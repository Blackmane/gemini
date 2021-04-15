/**
 * @file    Protocol.hpp
 * @brief   protocol informations
 *
 * @author  Niccolò Pieretti
 * @date    11 Apr 2021
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

#ifndef GEMINI_PROTOCOL
#define GEMINI_PROTOCOL

#include <string>

/**
 * @brief gemini projects
 */
namespace gemini {

/**
 * @brief carriage return
 */
const char CR = (char)13;
/**
 * @brief line feed
 */
const char LF = (char)10;

/**
 * @brief request protocol constants
 */
namespace request {

const size_t URL_MAX_SIZE = 1024;

} // namespace request

/**
 * @brief response protocol constants
 */
namespace response {

const size_t HEADER_STATUS_SIZE = 2; // bytes
const char HEADER_STATUS_FIRST_CHAR_MIN = '1';
const char HEADER_STATUS_FIRST_CHAR_MAX = '6';

const size_t HEADER_SPACE_SIZE = 1; // byte

const size_t HEADER_META_SIZE = 1024; // bytes

const size_t BODY_CHUNK_SIZE = 1024; // bytes

/**
 * @brief possibles value of first status digit
 */
enum HEADER_STATUS_FIRST {
  INPUT = 1,
  SUCCESS = 2,
  REDIRECT = 3,
  TEMPORARY_FAILURE = 4,
  PERMANENT_FAILURE = 5,
  CLIENT_CERTIFICATE_REQUIRED = 6
};

/**
 * @brief check value is a valid first status digit (1-6).
 * @param value a char value.
 * @return true if it is ok, false otherwise.
 */
bool isHeaderStatusFirstValid(const char value);

/**
 * @brief check value is a valid second status digit (0-9).
 * @param value a char value.
 * @return true if it is ok, false otherwise.
 */
bool isHeaderStatusSecondValid(const char value);

} // namespace response
} // namespace gemini

#endif /* GEMINI_PROTOCOL */
