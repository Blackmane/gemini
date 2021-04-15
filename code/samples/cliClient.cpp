/**
 * @file    cliClient.cpp
 * @brief   CLI client for gemini protocol
 *
 * @author  Niccolò Pieretti
 * @date    02 Apr 2021
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

#include "GeminiClient.hpp"
#include "Protocol.hpp"
#include "TslSocket.hpp"

#include <iostream>

#define PrintGetFROM(hostname, port)                                           \
  {                                                                            \
    std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;     \
    std::cout << "Get from: " << hostname << " : " << port << std::endl;       \
  }

#define PrintResponse(response)                                                \
  {                                                                            \
    std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;     \
    std::cout << "Response: " << response->statusCodeFirst                     \
              << response->statusCodeSecond << " " << response->meta           \
              << std::endl;                                                    \
    std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;     \
    if (response->body != "") {                                                \
      std::cout << response->body << std::endl;                                \
      std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;   \
    }                                                                          \
  }

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " <hostname> <port>\n" << std::endl;
    exit(1);
  }

  std::string hostname = argv[1];
  std::string port = argv[2];

  try {
    PrintGetFROM(hostname, port);
    auto response = gemini::GeminiClient::request(hostname, port);
    PrintResponse(response);
    while (response->statusCodeFirst == gemini::response::REDIRECT) {
      std::string input;
      std::cout << "\nRedirect to " << response->meta << "? (y/N)" << std::endl;
      std::cin >> input;
      if (!(input[0] == 'y' || input[0] == 'Y')) {
        break;
      }
      std::cout << std::endl;
      PrintGetFROM(response->meta, port);
      response = gemini::GeminiClient::request(response->meta, port);
      PrintResponse(response);
    }
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
}