cmake_minimum_required(VERSION 3.10)

project(shortUrl VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(nlohmann_json REQUIRED)

include_directories(src)
add_executable(shortUrl
        src/main.cpp
        src/ShortenUrl.cpp
)

target_include_directories(shortUrl PRIVATE include)