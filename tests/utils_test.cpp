/**
 * @file    utils_test.cpp
 * @brief   test suite for utils
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

#include "catch.hpp"

#include "Exception.hpp"
#include "Utils.hpp"


TEST_CASE( "Test getHostnameFromUrl", "[url2hostname]" ) {
    
    SECTION ("empty or incomplete url") {

        std::string hostname;
        // Missing schema
        REQUIRE_THROWS_AS (hostname = gemini::getHostnameFromUrl(""), gemini::invalid_schema);
        
        std::string wrongSchema("abc456de9");
        std::string schema("gemini://");
        REQUIRE (schema.length() == wrongSchema.length());

        // Missing schema
        REQUIRE_THROWS_AS (hostname = gemini::getHostnameFromUrl(wrongSchema), gemini::invalid_schema);
	}

    SECTION ("nice url") {

        std::string schema("gemini://");
        std::string hostname("example.com");

        std::string result;
        REQUIRE_NOTHROW (result = gemini::getHostnameFromUrl(std::string(schema + hostname + "/")));
        REQUIRE (result == hostname);

        REQUIRE_NOTHROW (result = gemini::getHostnameFromUrl(std::string(schema + hostname)));
        REQUIRE (result == hostname);

        REQUIRE_NOTHROW (result = gemini::getHostnameFromUrl(std::string(schema + hostname + "/dir/path/file.txt")));
        REQUIRE (result == hostname);
	}
}