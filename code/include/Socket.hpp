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
 ****************************************************************************
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

/**
 * @brief Virtual socket.
 */
class Socket {
public:
  /**
   * @brief create socket and connect.
   */
  Socket(){};
  /**
   * @brief free connection and delete socket.
   */
  ~Socket(){};
  /**
   * @brief Send a request via socket.
   * @param request a request.
   * @return number of bytes sent.
   */
  virtual int send(const std::string request) { return 0; };
  /**
   * @brief Read response via socket.
   * @param buffer allocated space where to save read bytes.
   * @param maxLength max number of bytes to read. Usually size of buffer.
   * @return number of bytes read.
   */
  virtual int read(char *buffer, int maxLength) { return 0; };
};

} // namespace gemini

#endif /* GEMINI_SOCKET */