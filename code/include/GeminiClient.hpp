/**
 * @file    GeminiClient.hpp
 * @brief   client wrapper for gemini protocol
 * 
 * @author  Niccolò Pieretti
 * @date    02 Apr 2021
 * @bug     cant use same socket twice
 * @todo    refactor
 * @todo    comment code
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#ifndef GEMINI_GEMINICLIENT
#define GEMINI_GEMINICLIENT

#include "Socket.hpp"

#include <memory>
#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    struct Response {

        uint statusCodeFirst;
        uint statusCodeSecond;

        std::string meta;
        std::string body;

        // TODO: handle copy
    };

    class GeminiClient {
    public:
        // TODO: commentare
        static std::unique_ptr<Response> request(const std::string hostname, const std::string port);
        static std::unique_ptr<Response> getResponse(std::string request, std::unique_ptr<Socket> socket);
    };

} // namespace gemini

#endif /* GEMINI_GEMINICLIENT */