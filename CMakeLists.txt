cmake_minimum_required(VERSION 3.10)

project(shortUrl VERSION 1.0 LANGUAGES CXX)

cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")
add_subdirectory("${LIBS_DIR}/nlohmann_json")

set(BOOST_ROOT "${LIBS_DIR}/boost")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(src)
add_executable(shortUrl
        src/main.cpp
        src/ShortenUrl.cpp
        src/RedirectServer.cpp
        src/RedirectServer.h
        src/ServerData.cpp
        src/ServerData.h
)

target_link_libraries(shortUrl PRIVATE ${Boost_LIBRARIES})
target_link_libraries(shortUrl PRIVATE nlohmann_json::nlohmann_json)

set(SOURCE_FILE "server_config.json")
file(COPY ${SOURCE_FILE} DESTINATION ${CMAKE_BINARY_DIR})