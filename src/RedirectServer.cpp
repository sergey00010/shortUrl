#include "RedirectServer.h"
#include <ShortenUrl.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>

namespace http = boost::beast::http;
namespace ip = boost::asio::ip;

using json = nlohmann::json;

RedirectServer::RedirectServer(const std::string &address, unsigned short port , const std::string &public_address)
    : acceptor(io_service)
{
    ip::tcp::endpoint endpoint(ip::address::from_string(address), port);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen();

    *public_addr = public_address;
}

void RedirectServer::run() {
    do_accept();
    io_service.run();
}

void RedirectServer::do_accept() {
    acceptor.async_accept(
        [this](boost::system::error_code ec, ip::tcp::socket socket) {
            if (ec) {
                std::cerr << "Error on accept: " << ec.message() << std::endl;
            } else {
                std::cout << "Accepted a new connection" << std::endl;

                ip::tcp::socket *socket_ptr = new ip::tcp::socket(std::move(socket));
                boost::beast::flat_buffer *buffer = new boost::beast::flat_buffer();
                http::request<http::string_body> *req = new http::request<http::string_body>();

                // Read response
                http::async_read(*socket_ptr, *buffer, *req,
                    [this, socket_ptr, buffer, req](boost::system::error_code ec, std::size_t length) {
                        if (ec) {
                            std::cerr << "Error on read: " << ec.message() << std::endl;
                            return;
                        }
                        std::cout << "Received " << length << " bytes" << std::endl;

                        auto res = new http::response<http::string_body>();
                        handle_request(*req, *res);

                        // Send answer
                        http::async_write(*socket_ptr, *res,
                            [socket_ptr, res](boost::system::error_code ec, std::size_t) {
                                if (ec) {
                                    std::cerr << "Error on write: " << ec.message() << std::endl;
                                }
                                socket_ptr->shutdown(ip::tcp::socket::shutdown_both);
                                socket_ptr->close();
                                std::cout << "Response sent." << std::endl;

                                delete socket_ptr;
                                delete res;
                            });
                        delete buffer;
                        delete req;
                    });
            }

            // Accept new connection
            do_accept();
        });
}

void RedirectServer::handle_request(http::request<http::string_body>& req,
                                     http::response<http::string_body>& res) {
    std::string path(req.target());

    if (path == "/api/createUrl" && req.method() == http::verb::post){
        try {
            // parse the incoming request to json
            auto parsed_json = json::parse(req.body());

            // extract the link
            std::string originalUrl = parsed_json.contains("url") ? parsed_json["url"].get<std::string>() : "";

            //create short url
            ShortenUrl shortenUrl;
            shortenUrl.loadFromJson("urls.json");
            std::string short_url = shortenUrl.shorten(originalUrl);
            shortenUrl.saveToJson("urls.json");

            // create json to send short url
            json json_response;
            json_response["short_url"] =  *public_addr + short_url;

            std::string body = json_response.dump();
            res.result(http::status::ok);
            res.set(http::field::content_type, "application/json");
            res.body() = body;
            res.set(http::field::content_length, std::to_string(body.size()));
        } catch (const json::exception& e) {
            // Обработка ошибки парсинга JSON
            res.result(http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = R"({"error":"Invalid JSON format"})";
            res.set(http::field::content_length, std::to_string(res.body().size()));
        }
    }else {
        ShortenUrl shortenUrl;
        shortenUrl.loadFromJson("urls.json");

        //find map
        std::unordered_map<std::string, std::string> url_map = shortenUrl.getMap();
        std::unordered_map<std::string, std::string>::iterator it = url_map.find(path);

        if (it != url_map.end()) {
            res.result(http::status::found);
            //redirect to long url
            res.set(http::field::location, it->second);
            res.set(http::field::content_length, "0");
        } else {
            res.result(http::status::not_found);
            res.set(http::field::content_length, "0");
        }
        res.set(http::field::connection, "close");
    }
}

void RedirectServer::stop() {
    io_service.stop();
    std::cout << "Server is stopping..." << std::endl;
}
