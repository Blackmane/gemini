# ===== ===== ===== Find libraries ===== ===== 

find_package(OpenSSL REQUIRED)
find_package (Threads)


# ===== ===== ===== Main Obj ===== ===== ===== 
add_library(MAIN_objs OBJECT main_catch.cpp)
target_compile_features(MAIN_objs PUBLIC cxx_std_11)

# ===== ===== ===== Tests ===== ===== ===== 

# ~~~~~ ~~~~~ Utils test ~~~~~ ~~~~~ 
add_executable(utilsTest 
    $<TARGET_OBJECTS:MAIN_objs>
    utils_test.cpp
    "${gemini_SOURCE_DIR}/code/include/Exception.hpp"
    "${gemini_SOURCE_DIR}/code/include/Utils.hpp"
    "${gemini_SOURCE_DIR}/code/src/Utils.cpp"
    )

target_compile_features(utilsTest PRIVATE cxx_std_11)
target_include_directories(utilsTest PRIVATE ../code/include)


target_link_libraries(utilsTest PRIVATE OpenSSL::SSL OpenSSL::Crypto )

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testutils COMMAND utilsTest) # Command can be a target


# ~~~~~ ~~~~~ Protocol test ~~~~~ ~~~~~ 
add_executable(protocolTest 
    $<TARGET_OBJECTS:MAIN_objs>
    protocol_test.cpp
    "${gemini_SOURCE_DIR}/code/include/Protocol.hpp"
    "${gemini_SOURCE_DIR}/code/src/Protocol.cpp"
    )

target_compile_features(protocolTest PRIVATE cxx_std_11)
target_include_directories(protocolTest PRIVATE ../code/include)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testprotocol COMMAND protocolTest) # Command can be a target


# ~~~~~ ~~~~~ Gemini Client test ~~~~~ ~~~~~ 
add_executable(geminiClientTest 
    $<TARGET_OBJECTS:MAIN_objs>
    geminiClient_test.cpp
    "${gemini_SOURCE_DIR}/code/include/Protocol.hpp"
    "${gemini_SOURCE_DIR}/code/include/Exception.hpp"
    "${gemini_SOURCE_DIR}/code/include/Utils.hpp"
    "${gemini_SOURCE_DIR}/code/include/GeminiClient.hpp"
    "${gemini_SOURCE_DIR}/code/include/Socket.hpp"
    "${gemini_SOURCE_DIR}/code/include/TslSocket.hpp"

    "${gemini_SOURCE_DIR}/code/src/Protocol.cpp"
    "${gemini_SOURCE_DIR}/code/src/Utils.cpp"
    "${gemini_SOURCE_DIR}/code/src/GeminiClient.cpp"
    "${gemini_SOURCE_DIR}/code/src/TslSocket.cpp"
    )

target_compile_features(geminiClientTest PRIVATE cxx_std_11)
target_include_directories(geminiClientTest PRIVATE ../code/include)


target_link_libraries(geminiClientTest PRIVATE OpenSSL::SSL OpenSSL::Crypto )

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testgeminiclient COMMAND geminiClientTest) # Command can be a target
