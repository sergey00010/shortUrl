#ifndef SHORTENURL_H
#define SHORTENURL_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <nlohmann/json.hpp>

class ShortenUrl {
public:
    ShortenUrl();
    std::string shorten(const std::string& long_url);
    std::string getOriginalURL(const std::string& short_url);
    void loadFromJson(const std::string& filename);
    void saveToJson(const std::string& filename);
    std::unordered_map<std::string, std::string>  getMap();

private:
    //shorts and original urls
    std::unordered_map<std::string, std::string> url_map;

    std::string generateShortURL();
    std::string base62Chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int counter;
};

#endif //SHORTENURL_H
