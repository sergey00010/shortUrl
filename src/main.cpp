#include <iostream>
#include <ShortenUrl.h>

int main() {
  ShortenUrl shortenUrl;

  // load data from json file
  shortenUrl.loadFromJson("urls.json");

  //std::string long_url;
  //std::cout << "Enter a long URL: ";
  //std::cin >> long_url;

  for(int i = 0;i<1000;i++){
    std::string long_url = std::to_string(i);
    //generate short url
    std::string short_url = shortenUrl.shorten(long_url);
    std::cout << "Shortened URL: http://127.0.0.1/" << short_url << std::endl;

    //Save data to json
    shortenUrl.saveToJson("urls.json");
  }

  // find original link from short url
  //std::cout << "Enter a short URL: ";
  //std::cin >> short_url;
  //std::cout << "Original URL: " << shortenUrl.getOriginalURL(short_url) << std::endl;

  return 0;
}