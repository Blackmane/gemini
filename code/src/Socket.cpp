/**
 * @file    Socket.cpp
 * @brief   implementation
 * 
 * @author  Niccolò Pieretti
 * @date    02 Apr 2021
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "Socket.hpp"
#include "Connection.hpp"


// ~~~~~ ~~~~~ ~~~~~
// Implementation
// ~~~~~ ~~~~~ ~~~~~

gemini::Socket::Socket() {

}

gemini::Socket::~Socket() {

}


std::unique_ptr<gemini::Connection> gemini::Socket::getConnection(const std::string hostname, const std::string port) {
    return std::unique_ptr<gemini::Connection>(new Connection());
}