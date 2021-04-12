/**
 * @file    Socket.hpp
 * @brief   Virtual socket
 * for testing purpose
 * 
 * @author  Niccolò Pieretti
 * @date    08 Apr 2021
 * @bug     
 * @todo    
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#ifndef GEMINI_SOCKET
#define GEMINI_SOCKET

#include "Connection.hpp"

#include <memory>
#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class Socket {
        public:
            Socket();
            ~Socket();
            virtual std::unique_ptr<Connection> getConnection(const std::string hostname, const std::string port);
    };

} // namespace gemini

#endif /* GEMINI_SOCKET */