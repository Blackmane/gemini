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

std::string askForInput(std::string meta);

void printResponse(gemini::Response *response);

bool askToRedirect(std::string newUrl);

void printFailure(std::string message, std::string meta);

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " <hostname> <port>\n" << std::endl;
    exit(1);
  }

  bool again = false;
  std::string hostname = argv[1];
  std::string port = argv[2];

  try {
    do {
      PrintGetFROM(hostname, port);
      auto response = gemini::GeminiClient::request(hostname, port);

      again = false;
      switch (response->statusCodeFirst) {
      case gemini::response::INPUT:
        // TODO: handle request with input
        askForInput(response->meta);
        again = true;
        // hostname = response->meta;
        break;
      case gemini::response::SUCCESS:
        printResponse(response.get());
        break;
      case gemini::response::REDIRECT:
        again = askToRedirect(response->meta);
        // TODO: check if is relative url
        hostname = response->meta;
        break;
      case gemini::response::TEMPORARY_FAILURE:
        printFailure("Temporary failure", response->meta);
        break;
      case gemini::response::PERMANENT_FAILURE:
        printFailure("Permanent failure", response->meta);
        break;
      case gemini::response::CLIENT_CERTIFICATE_REQUIRED:
        printFailure("Error with certificate", response->meta);
        break;
      default:
        break;
      }
    } while (again);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
}

std::string askForInput(std::string meta) {
  std::string input;
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  std::cout << "Response: ask for input: " << meta << std::endl;
  std::cin >> input;
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  return input;
}

void printResponse(gemini::Response *response) {
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  std::cout << "Response: " << response->statusCodeFirst
            << response->statusCodeSecond << " " << response->meta << std::endl;
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  if (response->body != "") {
    std::cout << response->body << std::endl;
    std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  }
}

bool askToRedirect(std::string newUrl) {
  std::string input;
  std::cout << "\nRedirect to " << newUrl << "? (y/N)" << std::endl;
  std::cin >> input;
  if (!(input[0] == 'y' || input[0] == 'Y')) {
    return false;
  }
  std::cout << std::endl;
  return true;
}

void printFailure(std::string message, std::string meta) {
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
  std::cout << "Failure: " << message << "\n" << meta << std::endl;
  std::cout << "----- ----- ----- ----- ----- ----- -----" << std::endl;
}