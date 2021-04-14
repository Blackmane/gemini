/**
 * @file    Utils.cpp
 * @brief   implementation
 * 
 * @author  Niccolò Pieretti
 * @date    06 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "Exception.hpp"
#include "Utils.hpp"

#include <iostream>

#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/err.h>


// ~~~~~ ~~~~~ ~~~~~
// Utils
// ~~~~~ ~~~~~ ~~~~~

int gemini::openConnection(const std::string hostname, const std::string port) {
    struct addrinfo hints;
    std::memset(&hints, 0, sizeof(addrinfo));
    struct addrinfo * addrs = nullptr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const int status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &addrs);
    if ( status != 0 ) {
        throw std::runtime_error("ERROR " + hostname + ":" + gai_strerror(status));
    }

    const int ERROR_STATUS = -1;
    int sfd, err;
    for (struct addrinfo *addr = addrs; addr != nullptr; addr = addr->ai_next) {
        sfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
        if (sfd == ERROR_STATUS) {
            err = errno;
            continue;
        }

        if (connect(sfd, addr->ai_addr, addr->ai_addrlen) == 0) {
            break;
        }

        err = errno;
        sfd = ERROR_STATUS;
        close(sfd);
    }

    freeaddrinfo(addrs);

    if (sfd == ERROR_STATUS) {
        throw std::runtime_error(hostname + ":" + strerror(err));
    }

    return sfd;
}


void gemini::displayCerts(SSL *ssl)  {
    X509 *cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != nullptr) {
        std::cout << "Server certificates:" << std::endl;
        char *line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        std::cout << "Subject: " << line << std::endl;
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        std::cout << "Issuer: " << line << std::endl;
        free(line);
        X509_free(cert);
    }
    else {
        std::cout << "Info: No client certificates configured." << std::endl;
    }
}


std::string gemini::getHostnameFromUrl(const std::string url) {
    // "gemini://url/path
    std::string schema ("gemini://");
    if (url.length() < schema.length()) {
        throw invalid_schema("Missing schema");
    }
    for (size_t i = 0; i < schema.length(); i++) {
        if (schema[i] != url[i]) {
            throw invalid_schema("Invalid schema");
        }
    }
    auto pos = url.find('/', schema.length());
    if (pos == std::string::npos) {
        // Slash missing, take all
        pos = url.length();
    }    
    return url.substr(schema.length(), pos - schema.length());
}