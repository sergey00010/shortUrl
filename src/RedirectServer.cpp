#include "RedirectServer.h"
#include <ShortenUrl.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace http = boost::beast::http;
namespace ip = boost::asio::ip;

RedirectServer::RedirectServer(const std::string& address, unsigned short port)
    : acceptor(io_service)
{
    ip::tcp::endpoint endpoint(ip::address::from_string(address), port);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen();
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

void RedirectServer::stop() {
    io_service.stop();
    std::cout << "Server is stopping..." << std::endl;
}
