cmake_minimum_required(VERSION 3.20)
project(INI_PARSER)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# --------------- Library --------------

add_library(ini_parser
    src/parser.cpp
)

target_include_directories(ini_parser PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# --------------- Main application -------------

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    ini_parser
)

# --------------- Tests -------------------
add_executable(${PROJECT_NAME}_TESTS
    tests/parser_tests.cpp
)
target_link_libraries(${PROJECT_NAME}_TESTS
    ini_parser
    GTest::gtest_main
)

target_compile_definitions(${PROJECT_NAME}_TESTS PRIVATE
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_TESTS WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})