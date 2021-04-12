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

#include "TslConnection.hpp"
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
            GeminiClient(std::unique_ptr<Socket> socket);
            ~GeminiClient();
            static std::unique_ptr<GeminiClient> getGeminiClient();
            Response request(const std::string hostname, const std::string port);
        private:

            std::unique_ptr<Socket> _socket;
    };

} // namespace gemini

#endif /* GEMINI_GEMINICLIENT */