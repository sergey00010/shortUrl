#include "ServerData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ServerData::ServerData() {

}

void ServerData::loadConfig(const std::string &filename, unsigned short &port, std::string &server_addr, std::string &server_public_addr) {
    unsigned short default_port = 9999;
    std::string default_server_addr = "192.168.1.199";
    std::string default_server_public_addr = "http://127.0.0.1";

    std::ifstream infile(filename);

    if (infile.is_open()) {
        try {
            json config;
            infile >> config;

            // load data about server if it exist
            port = config.value("port", default_port);
            server_addr = config.value("server_addr", default_server_addr);
            server_public_addr = config.value("server_public_addr", default_server_public_addr);

            std::cout << "server config is loaded : " << filename << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "error read json " << e.what() << std::endl;
        }
    } else {
        //set default value
        port = default_port;
        server_addr = default_server_addr;
        server_public_addr = default_server_public_addr;

        // if file with config don't exist than create it
        json config = {
            {"port", default_port},
            {"server_addr", default_server_addr},
            {"server_public_addr", default_server_public_addr}
        };

        std::ofstream outfile(filename);
        if (outfile.is_open()) {
            outfile << config.dump(4);
            std::cout << "server config created " << filename << std::endl;
        } else {
            std::cerr << "server confid file doesn't create " << filename << std::endl;
        }
    }
}

