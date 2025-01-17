/*
 *  create by Sergey Kuzmenko for infotecs
 *  in 2025 year
 *
 *  RedirectServer use to process requests coming to the server and
 *  redirect user to original url from short url (if short url exist in app)
 *
 *  ShortenUrl use to generate short url from original (long) url.
 *  The short address is created based on the link sequence number converted to a base62 number
 *
 * ServerData contains data about server, name, address, port, etc.
 * And it has to save to json and load from json
 *
 */

#include <iostream>
#include <ShortenUrl.h>
#include <RedirectServer.h>
#include <ServerData.h>
#include <thread>

int main() {
    unsigned short port;
    std::string server_addr;
    std::string server_public_addr;

    ServerData server_data;
    server_data.loadConfig("server_config.json",port, server_addr, server_public_addr);

    ShortenUrl &shortenUrl = ShortenUrl::getInstance();
    shortenUrl.loadFromJson("./urls/urls.json");

    try {
        std::thread server_thread([=]() {
            try {
                RedirectServer server(server_addr, port,server_public_addr);
                std::cout << "Server running on "<<server_public_addr<< std::endl;
                server.run();
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        });

        server_thread.join();

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}