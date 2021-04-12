/**
 * @file    Utils.hpp
 * @brief   utils functions
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

#ifndef GEMINI_UTILS
#define GEMINI_UTILS

#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    int openConnection(const std::string hostname, const std::string port);

    void displayCerts(SSL *ssl);

    std::string getHostnameFromUrl(const std::string url);

} // namespace gemini

#endif /* GEMINI_UTILS */