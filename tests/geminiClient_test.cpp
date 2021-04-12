/**
 * @file    geminiClient_test.cpp
 * @brief   test suite for gemini protocol
 * 
 * @author  Niccolò Pieretti
 * @date    08 Apr 2021
 * 
*******************************************************************************
 *                                         _                                  
 *                                        \_\                                 
 *                              ____ ____  _ /|_                              
 *                             / ___)  _ \| |  _|                             
 *                            ( (___| | | | | |___                            
 *                             \____)_| |_|_|\___/                            
 *                                                                            
 *****************************************************************************/

#include "catch.hpp"

#include "Exception.hpp"
#include "GeminiClient.hpp"
#include "Socket.hpp"
#include "Connection.hpp"

#include <algorithm>


#include <iostream>
#define println(MSG) std::cout<<MSG<<std::endl;

using namespace gemini;

class StubConnection : public gemini::Connection {
public:
    StubConnection() {

    }

    ~StubConnection() {

    }
    
    virtual int send(const std::string request) {
        return request.length();
    }

    virtual int read(char * buffer, int maxLength) {
        if (buffer == nullptr) {
            throw std::invalid_argument("Invalid buffer");
        }
        auto len = std::min( (size_t) maxLength, _response.length() - _index);
        for (size_t i = 0; i < len; i++) {
            buffer[i] = _response[_index + i];
        }
        _index += len;        
        return len;
    }

    void set(std::string response) {
        _response = response;
        _index = 0;
    }

    void check () {
        std::cout << _response << std::endl;
    }

private:
    std::string _response;
    size_t _index = 0;

};

class StubSocket : public gemini::Socket {
public:
    StubSocket() {
        connection = std::unique_ptr<gemini::Connection> (new StubConnection());
    }

    ~StubSocket() {

    }

    StubConnection* getStubConnection() {
        return (StubConnection *)connection.get();
    }

    virtual std::unique_ptr<gemini::Connection> getConnection(const std::string hostname, const std::string port) {
        return std::move(connection);
    }
private:
    std::unique_ptr<gemini::Connection> connection;
};



TEST_CASE( "Test stubs", "[socket/connection stub]" ) {
    
    SECTION ("connection creation") {
        StubConnection connection;
	}
    
    SECTION ("connection wrong use") {
        StubConnection connection;
        // Invalid arguments
        REQUIRE_THROWS_AS (connection.read(nullptr, 0), std::invalid_argument);
        // Empty read
        const size_t maxLength = 2048;
        char buffer[maxLength];
        buffer[0] = 'A';
        auto read = connection.read((char *) buffer, 0);
        REQUIRE (read == 0);
        REQUIRE (buffer[0] == 'A');
    }
    
    SECTION ("connection use") {
        StubConnection connection;
        // Send
        std::string message ("The quick brown fox jumps over the lazy dog");
        auto sent = connection.send(message);
        REQUIRE (sent == message.length());
        // Set data
        const size_t maxLength = 2048;
        char buffer[maxLength];
        std::string data("012456789");
        connection.set(data);
        // Read set data
        auto allRead = 0;
        auto read = connection.read((char *) buffer, 1);
        allRead += read;
        REQUIRE (read == 1);
        REQUIRE (buffer[0] == data[0]);
        read = connection.read((char *) buffer, 1);
        allRead += read;
        REQUIRE (read == 1);
        REQUIRE (buffer[0] == data[1]);
        // Read more chars
        read = connection.read((char *) buffer, 10);
        allRead += read;
        REQUIRE (allRead == data.length());
        for (auto i = 0; i < read; i++) {
            REQUIRE (buffer[i] == data[allRead - read + i]);
        }
        // All already read
        read = connection.read((char *) buffer, 10);
        REQUIRE (read == 0);
    }
    
    SECTION ("socket creation") {
        StubSocket socket;
        // Init stub connection
        auto * stubConnection = socket.getStubConnection();
        REQUIRE (stubConnection != nullptr);
        // getConnection should return a valid connection
        auto connection = socket.getConnection("", "");
        // The same of stub
        REQUIRE (stubConnection == connection.get());
        // stub should be nulled by move
        stubConnection = socket.getStubConnection();
        REQUIRE (stubConnection == nullptr);
	}

}


TEST_CASE( "Test gemini client creation", "[gemini client]" ) {
    
    SECTION ("Gemini client creation") {
        auto socket = gemini::GeminiClient::getGeminiClient();

        // TODO: request to know address
	}

}


TEST_CASE( "Test gemini client responses", "[gemini client]" ) {

    // Prepare stub socket and connection
    auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket());
    auto stubConnection = stubSocket->getStubConnection();
    // Use stub instead getGeminiClient
    auto client = new GeminiClient( std::move(stubSocket) );
    // Valid schema url
    std::string url("gemini://example.com");

    SECTION ("handle invalid argument") {
        // Invalid arguments: too long url
        std::string invalidUrl(1030, 'a');
        REQUIRE(invalidUrl.length() > 1024);
        REQUIRE_THROWS_AS (client->request(invalidUrl, ""), std::invalid_argument);
        // Empty url
        REQUIRE_THROWS_AS (client->request("", ""), gemini::invalid_schema);
        // Missing schema url
        REQUIRE_THROWS_AS (client->request("example.com", ""), gemini::invalid_schema);
    }
    
    SECTION ("handle empty response") {
        // Empty response
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("handle short response") {
        stubConnection->set("a\n");
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("handle invalid status response") {
        stubConnection->set("ac babcde\n");
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("handle invalid space response") {
        stubConnection->set("94babcde\n");
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("handle invalid termination response header") {
        stubConnection->set("60 babcde\n");
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("handle invalid status response") {
        stubConnection->set("94 babcde\r\n");
        REQUIRE_THROWS_AS (client->request(url, ""), gemini::protocol_response_error);
    }

    SECTION ("good response") {
        stubConnection->set("30 babcde\r\n");
        auto result = client->request(url, "");
        REQUIRE(result.statusCodeFirst == 3);
        REQUIRE(result.statusCodeSecond == 0);
        REQUIRE(result.meta == "babcde");
    }

    SECTION ("good response with body") {
        stubConnection->set("20 babcde\r\nbllll");
        auto result = client->request(url, "");
        REQUIRE(result.statusCodeFirst == 2);
        REQUIRE(result.statusCodeSecond == 0);
        REQUIRE(result.meta == "babcde");
        REQUIRE(result.body == "bllll");
    }


}