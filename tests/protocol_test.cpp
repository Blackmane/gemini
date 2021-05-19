/**
 * @file    protocol_test.cpp
 * @brief   test suite for protocol utils
 * 
 * @author  Niccolò Pieretti
 * @date    11 Apr 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "catch.hpp"

#include "Protocol.hpp"


using namespace gemini;


TEST_CASE( "Test protocol utils", "[protocol utils]" ) {
    
    SECTION ("not valid values") {
        std::string values("avwz0789\n\r!£");
        for(auto var : values) {
            REQUIRE_FALSE ( response::isHeaderStatusFirstValid(var) );
        }
	}

    SECTION ("valid values") {
        std::string values("123456");
        for(auto var : values) {
            REQUIRE ( response::isHeaderStatusFirstValid(var) );
        }
	}
    
}