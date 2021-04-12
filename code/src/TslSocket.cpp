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
#include "TslConnection.hpp"
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

gemini::TslSocket::TslSocket() {
    const SSL_METHOD * method = TLS_client_method();
    SSL_CTX * ctx = SSL_CTX_new(method);
    if ( ctx == nullptr ) {
        throw std::runtime_error("SSL_CTX() init failed");
        ERR_print_errors_fp(stderr);
    }

    ssl = SSL_new(ctx);
    if ( ssl == nullptr ) {
        SSL_CTX_free(ctx);
        throw std::runtime_error("SSL_new() failed");
    }
    SSL_CTX_free(ctx);
}

gemini::TslSocket::~TslSocket() {
    SSL_free(ssl);
}


std::unique_ptr<gemini::Connection> gemini::TslSocket::getConnection(const std::string hostname, const std::string port) {
    const int sfd = openConnection(hostname, port);
    SSL_set_fd(ssl, sfd);
    const int status = SSL_connect(ssl);
    if ( status != 1 ) {
        // TODO: throw exception
        SSL_get_error(ssl, status);
        ERR_print_errors_fp(stderr); //High probability this doesn't do anything
        std::cerr << "SSL_connect failed with SSL_get_error code " << status << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected with " << SSL_get_cipher(ssl) << " encryption" << std::endl;
    displayCerts(ssl);
    return std::unique_ptr<gemini::Connection>(new TslConnection(ssl, sfd));
}