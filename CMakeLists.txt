cmake_minimum_required(VERSION 3.10)

project(shortUrl VERSION 1.0 LANGUAGES CXX)

cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)

include_directories(src)
add_executable(shortUrl
        src/main.cpp
        src/ShortenUrl.cpp
        src/RedirectServer.cpp
        src/RedirectServer.h
        src/ServerData.cpp
        src/ServerData.h
)

set(SOURCE_FILE "server_config.json")
file(COPY ${SOURCE_FILE} DESTINATION ${CMAKE_BINARY_DIR})