/**
 * @file    TslConnection.cpp
 * @brief   implementation
 * 
 * @author  Niccolò Pieretti
 * @date    07 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "TslConnection.hpp"

#include <unistd.h>
#include <stdexcept>
#include <string.h>
#include <openssl/err.h>


// ~~~~~ ~~~~~ ~~~~~
// Implementation
// ~~~~~ ~~~~~ ~~~~~

gemini::TslConnection::TslConnection(SSL * ssl, const int sfd) : 
    _ssl(ssl), _sfd(sfd) {

}

gemini::TslConnection::~TslConnection() {
    close(_sfd);
}

int gemini::TslConnection::send(const std::string request) {
    return SSL_write(_ssl, request.c_str(), request.length());
}

int gemini::TslConnection::read(char * buffer, int maxLength) {
    if (buffer == nullptr) {
        throw std::invalid_argument("Invalid buffer");
    }
    return SSL_read(_ssl, buffer, maxLength);
}