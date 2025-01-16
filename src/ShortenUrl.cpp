#include "ShortenUrl.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

std::unique_ptr<ShortenUrl> ShortenUrl::instance = nullptr;
std::once_flag ShortenUrl::initInstanceFlag;

ShortenUrl::ShortenUrl() {
    counter = 0;
}

std::string ShortenUrl::shorten(const std::string& long_url) {
    std::string short_url = generateShortURL();
    url_map[short_url] = long_url;
    return short_url;
}

std::string ShortenUrl::getOriginalURL(const std::string& short_url) {
    // find original link from short
    return url_map.find(short_url) != url_map.end() ? url_map[short_url] : "URL not found!";
}

std::string ShortenUrl::generateShortURL() {
    std::string short_url;
    int num = counter++;

    //generate short url from long url with Base62
    while (num > 0) {
        short_url.push_back(base62Chars[num % 62]);
        num /= 62;
    }

    //return one symbol if result is empty
    if (short_url.empty())
        short_url.push_back(base62Chars[0]);
    return "/"+short_url;
}

std::unordered_map<std::string, std::string>  ShortenUrl::getMap() {
    return url_map;
}

void ShortenUrl::loadFromJson(const std::string& filename) {
    std::ifstream input_file(filename);
    if (input_file.is_open()) {
        json j;
        input_file >> j;

        // load data
        url_map = j.get<std::unordered_map<std::string, std::string>>();
        counter = url_map.size();
        input_file.close();
    }
}

void ShortenUrl::saveToJson(const std::string& filename) {
    std::ofstream output_file(filename);
    if (output_file.is_open()) {
        json j = url_map;
        output_file << j.dump(4); // write to json
        output_file.close();
    }
}


