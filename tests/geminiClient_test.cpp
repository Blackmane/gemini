/**
 * @file    geminiClient_test.cpp
 * @brief   test suite for gemini protocol
 * 
 * @author  Niccolò Pieretti
 * @date    08 Apr 2021
 * 
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "catch.hpp"

#include "Exception.hpp"
#include "GeminiClient.hpp"
#include "Socket.hpp"

#include <algorithm>
#include <memory>


#include <iostream>
#define println(MSG) std::cout<<MSG<<std::endl;

using namespace gemini;

// ~~~~~ ~~~~~ ~~~~~
// Stub class
// ~~~~~ ~~~~~ ~~~~~

class StubSocket : public gemini::Socket {
public:
    StubSocket(std::string response) {
        _response = response;
        _index = 0;
    }

    ~StubSocket() {

    }
    
    virtual int send(const std::string request) {
        return request.length();
    }

    virtual size_t read(char * buffer, size_t maxLength) {
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

    void check () {
        std::cout << _response << std::endl;
    }

private:
    std::string _response;
    size_t _index = 0;
};


// ~~~~~ ~~~~~ ~~~~~
// Tests
// ~~~~~ ~~~~~ ~~~~~

TEST_CASE( "Test stubs", "[socket/connection stub]" ) {
    
    SECTION ("connection creation") {
        StubSocket socket("");
	}
    
    SECTION ("connection wrong use") {
        StubSocket socket("");
        // Invalid arguments
        REQUIRE_THROWS_AS (socket.read(nullptr, 0), std::invalid_argument);
        // Empty read
        const size_t maxLength = 2048;
        char buffer[maxLength];
        buffer[0] = 'A';
        auto read = socket.read((char *) buffer, 0);
        REQUIRE (read == 0);
        REQUIRE (buffer[0] == 'A');
    }
    
    SECTION ("connection use") {
        std::string data("012456789");
        StubSocket socket(data);
        // Send
        std::string message ("The quick brown fox jumps over the lazy dog");
        auto sent = socket.send(message);
        REQUIRE (sent == message.length());
        // Set data
        const size_t maxLength = 2048;
        char buffer[maxLength];
        // Read set data
        auto allRead = 0;
        auto read = socket.read((char *) buffer, 1);
        allRead += read;
        REQUIRE (read == 1);
        REQUIRE (buffer[0] == data[0]);
        read = socket.read((char *) buffer, 1);
        allRead += read;
        REQUIRE (read == 1);
        REQUIRE (buffer[0] == data[1]);
        // Read more chars
        read = socket.read((char *) buffer, 10);
        allRead += read;
        REQUIRE (allRead == data.length());
        for (auto i = 0u; i < read; i++) {
            REQUIRE (buffer[i] == data[allRead - read + i]);
        }
        // All already read
        read = socket.read((char *) buffer, 10);
        REQUIRE (read == 0);
    }

}


TEST_CASE( "Test gemini client responses", "[gemini client]" ) {

    // // Prepare stub socket and connection
    // auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket());
    // auto stubSocket = stubSocket->getStubSocket();
    // // Use stub instead getGeminiClient
    // auto client = new GeminiClient( std::move(stubSocket) );
    // // Valid schema url
    // std::string url("gemini://example.com");

    // SECTION ("handle invalid argument") {
    //     // Invalid arguments: too long url
    //     std::string invalidUrl(1030, 'a');
    //     REQUIRE(invalidUrl.length() > 1024);
    //     REQUIRE_THROWS_AS (client->request(invalidUrl, ""), std::invalid_argument);
    //     // Empty url
    //     REQUIRE_THROWS_AS (client->request("", ""), gemini::invalid_schema);
    //     // Missing schema url
    //     REQUIRE_THROWS_AS (client->request("example.com", ""), gemini::invalid_schema);
    // }
    
    SECTION ("handle empty response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket(""));
        // Empty response
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("handle short response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("a\n"));
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("handle invalid status response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("ac babcde\n"));
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("handle invalid space response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("94babcde\n"));
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("handle invalid termination response header") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("60 babcde\n"));
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("handle invalid status response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("94 babcde\r\n"));
        REQUIRE_THROWS_AS (GeminiClient::getResponse(" ", std::move(stubSocket)), gemini::protocol_response_error);
    }

    SECTION ("good response") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("30 babcde\r\n"));
        auto result = GeminiClient::getResponse(" ", std::move(stubSocket));
        REQUIRE(result->statusCodeFirst == 3);
        REQUIRE(result->statusCodeSecond == 0);
        REQUIRE(result->meta == "babcde");
    }

    SECTION ("good response with body") {
        auto stubSocket = std::unique_ptr<StubSocket>(new StubSocket("20 babcde\r\nbllll"));
        auto result = GeminiClient::getResponse(" ", std::move(stubSocket));
        REQUIRE(result->statusCodeFirst == 2);
        REQUIRE(result->statusCodeSecond == 0);
        REQUIRE(result->meta == "babcde");
        REQUIRE(result->body == "bllll");
    }


}