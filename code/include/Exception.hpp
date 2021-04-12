/**
 * @file    Exception.hpp
 * @brief   Gemini exceptions
  * 
 * @author  Niccolò Pieretti
 * @date    09 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#ifndef GEMINI_EXCEPTION
#define GEMINI_EXCEPTION

#include <stdexcept>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

    class invalid_schema : public std::runtime_error {
    public:
        invalid_schema(const std::string &message) noexcept : 
            runtime_error(message) {}
    };

    class protocol_response_error : public std::runtime_error {
    public:
        protocol_response_error(const std::string &message) noexcept : 
            runtime_error(message) {}
    };

    class connection_error : public std::runtime_error {
    public:
        connection_error(const std::string &message) noexcept : 
            runtime_error(message) {}
    };

} // namespace gemini

#endif /* GEMINI_EXCEPTION */