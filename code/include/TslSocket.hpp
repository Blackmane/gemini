/**
 * @file    TslSocket.hpp
 * @brief   TSL socket
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

#ifndef GEMINI_TSLSOCKET
#define GEMINI_TSLSOCKET

#include "Socket.hpp"
#include "Connection.hpp"

#include <memory>
#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class TslSocket : public Socket {
        public:
            TslSocket();
            ~TslSocket();
            virtual std::unique_ptr<Connection> getConnection(const std::string hostname, const std::string port);

        private:
            SSL * ssl = nullptr;
    };

} // namespace gemini

#endif /* GEMINI_TSLSOCKET */