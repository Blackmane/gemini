/**
 * @file    TslConnection.hpp
 * @brief   TSL socket connection
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

#ifndef GEMINI_TSLCONNECTION
#define GEMINI_TSLCONNECTION

#include "Connection.hpp"

#include <exception>
#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class TslConnection : public Connection {
        public:
            TslConnection(SSL * ssl, const int sfd);
            ~TslConnection();
            
            virtual int send(const std::string request);
            virtual int read(char * buffer, int maxLength);

        private:
            SSL * _ssl = nullptr;
            int _sfd;
    };

} // namespace gemini

#endif /* GEMINI_TSLCONNECTION */