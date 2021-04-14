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

#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class Socket {
        public:
            Socket() {};
            ~Socket() {};
            virtual int send(const std::string request) { return 0; };
            virtual int read(char * buffer, int maxLength) { return 0; };
    };

} // namespace gemini

#endif /* GEMINI_SOCKET */