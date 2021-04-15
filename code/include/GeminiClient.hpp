/**
 * @file    GeminiClient.hpp
 * @brief   client wrapper for gemini protocol
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

#ifndef GEMINI_GEMINICLIENT
#define GEMINI_GEMINICLIENT

#include "Socket.hpp"

#include <memory>
#include <openssl/ssl.h>
#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

/**
 * @brief Response is the content, packed, of a response.
 */
struct Response {
  /**
   * @brief First digit of status code.
   */
  uint statusCodeFirst;
  /**
   * @brief Second digit of status code.
   */
  uint statusCodeSecond;
  /**
   * @brief Meta of the response.
   */
  std::string meta;
  /**
   * @brief Body of the response.
   */
  std::string body;

  // TODO: handle copy
};

/**
 * @brief GeminiClient handle a one shot gemini communication.
 */
class GeminiClient {
public:
  /**
   * @brief Create and send a gemini request to url:port.
   * @param url a gemini valid url in the format gemini://example.org/ .
   * @param port used port. Standard port is 1975.
   * @return a pointer to the response, or throw an exception in case of
   * failure.
   */
  static std::unique_ptr<Response> request(const std::string url,
                                           const std::string port);
  /**
   * @brief Send a request via socket and get the response.
   * For test purpose. Used by request.
   * @param request a gemini valid request.
   * @param socket a pointer to used socket.
   * @return a pointer to the response, or throw an exception in case of
   * failure.
   */
  static std::unique_ptr<Response> getResponse(std::string request,
                                               std::unique_ptr<Socket> socket);
};

} // namespace gemini

#endif /* GEMINI_GEMINICLIENT */