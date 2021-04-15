/**
 * @file    TslSocket.cpp
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

#include "TslSocket.hpp"
#include "Utils.hpp"

#include <errno.h>
#include <iostream>
#include <exception>
#include <netdb.h>
#include <resolv.h>
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <openssl/err.h>


// ~~~~~ ~~~~~ ~~~~~
// Implementation
// ~~~~~ ~~~~~ ~~~~~

gemini::TslSocket::TslSocket(const std::string hostname, const std::string port) {
    initCert();
    connect(hostname, port);
}


gemini::TslSocket::~TslSocket() {
    SSL_free(_ssl);
    close(_sfd);
}

int gemini::TslSocket::send(const std::string request) {
    return SSL_write(_ssl, request.c_str(), request.length());
}

int gemini::TslSocket::read(char * buffer, int maxLength) {
    if (buffer == nullptr) {
        throw std::invalid_argument("Invalid buffer");
    }
    return SSL_read(_ssl, buffer, maxLength);
}


void gemini::TslSocket::initCert() {
    const SSL_METHOD * method = TLS_client_method();
    SSL_CTX * ctx = SSL_CTX_new(method);
    if ( ctx == nullptr ) {
        throw std::runtime_error("SSL_CTX() init failed");
    }

    _ssl = SSL_new(ctx);
    if ( _ssl == nullptr ) {
        SSL_CTX_free(ctx);
        throw std::runtime_error("SSL_new() failed");
    }
    SSL_CTX_free(ctx);
}


void gemini::TslSocket::connect(const std::string hostname, const std::string port) {
    _sfd = openConnection(hostname, port);
    SSL_set_fd(_ssl, _sfd);
    const int status = SSL_connect(_ssl);
    if ( status != 1 ) {
        close(_sfd);
        SSL_get_error(_ssl, status);
        throw std::runtime_error("SSL_connect failed with SSL_get_error code " + status);
    }

    printCerts();
}

void gemini::TslSocket::printCerts() {
    std::cout << "Connected with " << SSL_get_cipher(_ssl) << " encryption" << std::endl;
    displayCerts(_ssl);
}