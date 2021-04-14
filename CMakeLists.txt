cmake_minimum_required(VERSION 3.11)

project(gemini
    VERSION 0.1
    DESCRIPTION "Gemini library"
    )

# Testing only available if this is the main app
# Note this needs to be done in the main CMakeLists
# since it calls enable_testing, which must be in the
# main CMakeLists.
if (ENABLE_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)





# Only do these if this is the main project, and not if it is included through 
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    #target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_11)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)
    # Enable clang-tidy
#    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=include;-checks=*")

# https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
    add_compile_options(
        -Wall -Wextra -Wno-unused-parameter 
        -pedantic 
        -Wshadow -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -ffunction-sections -fdata-sections
        -pie
        "$<$<CONFIG:RELEASE>:-Werror;-g3;-O2>"
        # $<$<NOT:$<CONFIG:DEBUG>>:-O2> 
        "$<$<CONFIG:TSAN>:-fsanitize=thread;-g;-O1>"
        "$<$<CONFIG:ASAN>:-fsanitize=address;-fno-optimize-sibling-calls;-fsanitize-address-use-after-scope;-fno-omit-frame-pointer;-g;-O1>"
        "$<$<CONFIG:LSAN>:-fsanitize=leak;-fno-omit-frame-pointer;-g;-O1>"
        # "$<$<CONFIG:MSAN>:-fsanitize=memory;-fno-optimize-sibling-calls;-fsanitize-memory-track-origins=2;-fno-omit-frame-pointer;-g;-O2>"
        "$<$<CONFIG:UBSAN>:-fsanitize=undefined>"
        -fPIC)

    add_link_options(
        $<$<CONFIG:TSAN>:-fsanitize=thread> 
        $<$<CONFIG:ASAN>:-fsanitize=address>
        $<$<CONFIG:TSAN>:-fsanitize=leak>
        #$<$<CONFIG:MSAN>:-fsanitize=memory>
        $<$<CONFIG:UBSAN>:-fsanitize=undefined> 
        )

    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
    
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Adding an option to switch on or off compilation of tests
    option (ENABLE_TESTING "Set to ON to perform unit tests" OFF)
    # Adding an option to switch on or off building of documentation
    option(BUILD_DOC "Set to ON to build documentation" OFF)

    if (ENABLE_TESTING)
        enable_testing()
        add_subdirectory(tests)
    endif ()

    if (BUILD_DOC)
        # Docs only available if this is the main app
        find_package(Doxygen)
        if (BUILD_DOCDoxygen_FOUND)
            add_subdirectory(doc)
        else()
            message(STATUS "Doxygen not found, not building docs")
        endif()
    endif()
endif()


add_subdirectory (code)