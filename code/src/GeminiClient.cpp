/**
 * @file    GeminiClient.cpp
 * @brief   implementation
 * 
 * @author  Niccolò Pieretti
 * @date    02 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "Protocol.hpp"
#include "Exception.hpp"
#include "GeminiClient.hpp"
#include "TslConnection.hpp"
#include "TslSocket.hpp"

#include "Utils.hpp"

#include <iostream>

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/err.h>

// ~~~~~ ~~~~~ ~~~~~
// Implementation
// ~~~~~ ~~~~~ ~~~~~

gemini::GeminiClient::GeminiClient(std::unique_ptr<Socket> socket) : _socket(std::move(socket)) {
    
}


gemini::GeminiClient::~GeminiClient() {
    
}


std::unique_ptr<gemini::GeminiClient> gemini::GeminiClient::getGeminiClient() {
    return std::unique_ptr<GeminiClient>(
                new GeminiClient(std::unique_ptr<Socket>(new TslSocket())                )
            );
}


gemini::Response gemini::GeminiClient::request(const std::string url, const std::string port) {
    // Check url
    if (url.length() > 1024) {
        throw std::invalid_argument("Invalid url length: expected max 1024");
    }
    // open connection
    const std::string hostname = getHostnameFromUrl(url);
    auto connection = _socket->getConnection(hostname, port);
    if (connection == nullptr) {
        throw connection_error("Error in connection to " + hostname + ":" + port);
    }
    // Build request
    std::string request(url + gemini::CR + gemini::LF); // <URL><CR><LF> 
    // Send request
    auto sendRes = connection->send(request);
    if (sendRes <= 0) {
        throw connection_error("Error in send request");
    }

    // Read <STATUS><SPACE>
    const auto statusSize = response::HEADER_STATUS_SIZE + response::HEADER_SPACE_SIZE;
    char statusBuffer[statusSize + 1];
    auto statusRes = connection->read(statusBuffer, statusSize);
    if ((size_t) statusRes < statusSize) {
        throw protocol_response_error("Empty response");
    }

    if ( !( response::isHeaderStatusFirstValid(statusBuffer[0])
            && response::isHeaderStatusSecondValid(statusBuffer[1]) ) ) {
        throw protocol_response_error("Invalid status --- response");
    }
    if ( statusBuffer[2] != ' ' ) {
        throw protocol_response_error("Invalid status response");
    }
    Response response;
    response.statusCodeFirst = statusBuffer[0] - '0';
    response.statusCodeSecond = statusBuffer[1] - '0';

    // Read <META><CR><FL>
    const auto metaSize = response::HEADER_META_SIZE + 2;
    char metaBuffer[metaSize + 1];
    auto metaRes = connection->read(metaBuffer, metaSize);
    // Check header termination
    if ( metaRes < 2 ) {
        throw protocol_response_error("Empty header");
    }
    // Assure metaBuffer terminates
    metaBuffer[metaRes > metaSize ? metaSize : metaRes] = '\0';
    // Find terminators
    auto pos = strstr (metaBuffer, "\r\n");
    if (pos == nullptr) {
        throw protocol_response_error("Invalid header termination");
    }
    if ((size_t) (pos - metaBuffer) > response::HEADER_META_SIZE) {
        throw protocol_response_error("Invalid meta size");
    }
    // Save meta
    response.meta = std::string(metaBuffer, pos);

    // Read <BODY>
    if (response.statusCodeFirst == response::HEADER_STATUS_FIRST::SUCCESS) {
        const auto bodyChunkSize = response::BODY_CHUNK_SIZE;
        char bodyBuffer[bodyChunkSize + 1];
        // Copy previous part
        if (pos+2 < metaBuffer + metaRes) {
           response.body += std::string(pos+2, metaBuffer + metaRes); 
            std::cout<< "OK<" << response.body << ">" << std::endl;
        }
        auto bodyRes = connection->read(bodyBuffer, bodyChunkSize);
        while (bodyRes > 0) {
            // Set string terminator
            bodyBuffer[(size_t)bodyRes > bodyChunkSize ? bodyChunkSize : bodyRes] = '\0';
            response.body += std::string(bodyBuffer);
            bodyRes = connection->read(bodyBuffer, bodyChunkSize);
        }
    }

    return response;
}
