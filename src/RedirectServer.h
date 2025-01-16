#ifndef REDIRECTSERVER_H
#define REDIRECTSERVER_H

#include <boost/beast/http.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

/*
 * RedirectServer use to process requests coming to the server and
 * redirect user to original url from short url (if short url exist in app)
 */

class RedirectServer {
public:
    //in constructor set server address and port
    RedirectServer(const std::string &address, unsigned short port ,const std::string &public_address);
    //run server
    void run();
    void stop();

private:
    //accept incoming connections and respond them
    void do_accept();

    //set original url from short url
    void handle_request(boost::beast::http::request<boost::beast::http::string_body>& req,
                        boost::beast::http::response<boost::beast::http::string_body>& res);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;

    std::string *public_addr;
};



#endif //REDIRECTSERVER_H
