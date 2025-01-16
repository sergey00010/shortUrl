#ifndef SHORTENURL_H
#define SHORTENURL_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <nlohmann/json.hpp>

/*
 * ShortenUrl use to generate short url from original (long) url.
 * The short address is created based on the link sequence number converted to a base62 number
 */
class ShortenUrl {
public:
    ShortenUrl();

    //get short url from original url (if exist)
    std::string shorten(const std::string& long_url);
    //get long url from short url
    std::string getOriginalURL(const std::string& short_url);

    //load and save short and original url
    //in format shortUrl:OriginalUrl
    //to json file
    void loadFromJson(const std::string& filename);
    void saveToJson(const std::string& filename);

    //get map in another class
    std::unordered_map<std::string, std::string>  getMap();

private:
    //shorts and original urls
    std::unordered_map<std::string, std::string> url_map;

    //generate short url from original url
    //use converting to Base62 number system
    std::string generateShortURL();
    std::string base62Chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int counter;
};

#endif //SHORTENURL_H
