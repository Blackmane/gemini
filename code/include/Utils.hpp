/**
 * @file    Utils.hpp
 * @brief   utils functions
 *
 * @author  Niccolò Pieretti
 * @date    06 Apr 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#ifndef GEMINI_UTILS
#define GEMINI_UTILS

#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

/**
 * @brief open a connection to hostname:port.
 * @param hostname
 * @param port
 * @return file descriptor.
 */
int openConnection(const std::string hostname, const std::string port);

/**
 * @brief print information about ssl cert.
 * @param ssl ssl certificate.
 */
void displayCerts(SSL *ssl);

/**
 * @brief get hostname from url.
 * @param url a gemini url. In format gemini://example.org .
 * @return hostname.
 */
std::string getHostnameFromUrl(const std::string url);

} // namespace gemini

#endif /* GEMINI_UTILS */