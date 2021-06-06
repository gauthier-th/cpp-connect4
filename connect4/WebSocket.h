#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>

#include "json.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using nlohmann::json;

class WebSocket : public std::enable_shared_from_this<WebSocket>
{
private:
    tcp::resolver resolver_;
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::string host_;
    std::string text_;

    void fail(beast::error_code ec, char const* what);
    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);
    void on_handshake(beast::error_code ec);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void on_close(beast::error_code ec);

    std::function<void(json)> _readCallback = nullptr;
    std::function<void()> _connectCallback = nullptr;

public:
    explicit WebSocket(net::io_context& ioc);

    void connect(char const* host, char const* port);
    void connect(char const* host, char const* port, std::function<void()> connectCallback);
    void write(std::string text);
    void setReadCallback(std::function<void(json)> readCallback);
    void close();

    void listGames();
    void createGame(std::string username);
};