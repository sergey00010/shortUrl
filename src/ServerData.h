//
// Created by forcks on 16.01.25.
//

#ifndef SERVERDATA_H
#define SERVERDATA_H

/*
 * ServerData has to save to json and load from json data about server
 * public address, id_address, port
 */

#include <iostream>

class ServerData {
public:
    ServerData();
    void loadConfig(const std::string& filename, unsigned short& port, std::string& server_addr,std::string& server_public_addr);
};



#endif //SERVERDATA_H
