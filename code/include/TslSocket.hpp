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

#include <string>
#include <openssl/ssl.h>

/**
 * @brief gemini projects
 */
namespace gemini {

    class TslSocket : public Socket {
        public:
            TslSocket(const std::string hostname, const std::string port);
            ~TslSocket();
            
            virtual int send(const std::string request);
            virtual int read(char * buffer, int maxLength);

        private:
            void initCert();
            void connect(const std::string hostname, const std::string port);
            void printCerts();

            SSL * _ssl = nullptr;
            int _sfd;
    };

} // namespace gemini

#endif /* GEMINI_TSLSOCKET */