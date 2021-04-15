/**
 * @file    Protocol.cpp
 * @brief   implementation
 *
 * @author  Niccolò Pieretti
 * @date    12 Apr 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "Protocol.hpp"

bool gemini::response::isHeaderStatusFirstValid(const char value) {
  return HEADER_STATUS_FIRST_CHAR_MIN <= value &&
         value <= HEADER_STATUS_FIRST_CHAR_MAX;
}

bool gemini::response::isHeaderStatusSecondValid(const char value) {
  return '0' <= value && value <= '9';
}