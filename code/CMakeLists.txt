# ===== ===== ===== Find libraries ===== ===== ===== 

find_package(OpenSSL REQUIRED)

# ===== ===== ===== Source code ===== ===== ===== 

set(GEMINI_HEADER_LIST 
    "${gemini_SOURCE_DIR}/code/include/Protocol.hpp"
    "${gemini_SOURCE_DIR}/code/include/GeminiClient.hpp"
    "${gemini_SOURCE_DIR}/code/include/Exception.hpp"
    "${gemini_SOURCE_DIR}/code/include/Connection.hpp"
    "${gemini_SOURCE_DIR}/code/include/TslConnection.hpp"
    "${gemini_SOURCE_DIR}/code/include/Socket.hpp"
    "${gemini_SOURCE_DIR}/code/include/TslSocket.hpp"
    "${gemini_SOURCE_DIR}/code/include/Utils.hpp"
    )

set(GEMINI_SRC_LIST 
    "${gemini_SOURCE_DIR}/code/src/Protocol.cpp"
    "${gemini_SOURCE_DIR}/code/src/GeminiClient.cpp"
    "${gemini_SOURCE_DIR}/code/src/Connection.cpp"
    "${gemini_SOURCE_DIR}/code/src/TslConnection.cpp"
    "${gemini_SOURCE_DIR}/code/src/Socket.cpp"
    "${gemini_SOURCE_DIR}/code/src/TslSocket.cpp"
    "${gemini_SOURCE_DIR}/code/src/Utils.cpp"
    )


# ===== ===== ===== Samples ===== ===== 

# CliClient
add_executable (CliClient 
    ${GEMINI_HEADER_LIST} 
    ${GEMINI_SRC_LIST}
    samples/cliClient.cpp )
target_include_directories(CliClient PRIVATE include/)
target_compile_features(CliClient PRIVATE cxx_std_11)
target_link_libraries (CliClient PRIVATE OpenSSL::SSL OpenSSL::Crypto )
