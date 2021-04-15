/**
 * @file    TslSocket.hpp
 * @brief   TSL socket
 *
 * @author  Niccolò Pieretti
 * @date    06 Apr 2021
 *
 ****************************************************************************
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

#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

/**
 * @brief TSL socket.
 */
class TslSocket : public Socket {
public:
  /**
   * @brief create a TSL socket and connect to hostname:port.
   * @param hostname
   * @param port
   */
  TslSocket(const std::string hostname, const std::string port);
  /**
   * @brief free connection and delete socket.
   */
  ~TslSocket();
  /**
   * @brief Send a request via socket.
   * @param request a request.
   * @return number of bytes sent.
   */
  virtual int send(const std::string request);
  /**
   * @brief Read response via socket.
   * @param buffer allocated space where to save read bytes.
   * @param maxLength max number of bytes to read. Usually size of buffer.
   * @return number of bytes read.
   */
  virtual int read(char *buffer, int maxLength);

private:
  /**
   * @brief initialize SSL certs. Init _ssl.
   */
  void initCert();
  /**
   * @brief open a connection to hostname:port. Init _sfd.
   * @param hostname
   * @param port
   */
  void connect(const std::string hostname, const std::string port);
  /**
   * @brief print information about ssl cert.
   */
  void printCerts();

  /**
   * @brief ssl certificate.
   */
  SSL *_ssl = nullptr;
  /**
   * @brief file descriptor of socket connected.
   */
  int _sfd;
};

} // namespace gemini

#endif /* GEMINI_TSLSOCKET */