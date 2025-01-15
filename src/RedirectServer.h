#ifndef REDIRECTSERVER_H
#define REDIRECTSERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class RedirectServer {
public:
    RedirectServer(const std::string& address, unsigned short port);
    void run();
    void stop();

private:
    void do_accept();
    void handle_request(boost::beast::http::request<boost::beast::http::string_body>& req,
                        boost::beast::http::response<boost::beast::http::string_body>& res);
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;
};



#endif //REDIRECTSERVER_H
