/**
 * @file    Connection.hpp
 * @brief   Virtual socket connection
 * for testing purpose
 * 
 * @author  Niccolò Pieretti
 * @date    08 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#ifndef GEMINI_CONNECTION
#define GEMINI_CONNECTION

#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class Connection {
        public:
            Connection();
            ~Connection();
            
            virtual int send(const std::string request);
            virtual int read(char * buffer, int maxLength);
    };

} // namespace gemini

#endif /* GEMINI_CONNECTION */