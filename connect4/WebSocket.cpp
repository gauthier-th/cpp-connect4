#include "WebSocket.h"
#include <ostream>

// Resolver and socket require an io_context
WebSocket::WebSocket(net::io_context& ioc) : resolver_(ioc), ws_(ioc) {}

void WebSocket::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Start the asynchronous operation
void WebSocket::connect(char const* host, char const* port)
{
    // Save this for later
    this->host_ = host;

    // Look up the domain name
    this->resolver_.async_resolve(host, port,
        beast::bind_front_handler(
            &WebSocket::on_resolve,
            shared_from_this()
        )
    );
}
// Start the asynchronous operation
void WebSocket::connect(char const* host, char const* port, websocket_callback connectCallback)
{
    this->_connectCallback = connectCallback;
    this->connect(host, port);
}

void WebSocket::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
    if (ec)
        return fail(ec, "resolve");

    // Set the timeout for the operation
    beast::get_lowest_layer(this->ws_).expires_after(std::chrono::seconds(30));

    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(this->ws_).async_connect(
        results,
        beast::bind_front_handler(
            &WebSocket::on_connect,
            shared_from_this()
        )
    );
}

void WebSocket::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if (ec)
        return fail(ec, "connect");

    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(this->ws_).expires_never();

    // Set suggested timeout settings for the websocket
    this->ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

    // Update the host_ string. This will provide the value of the
    // Host HTTP header during the WebSocket handshake.
    // See https://tools.ietf.org/html/rfc7230#section-5.4
    this->host_ += ':' + std::to_string(ep.port());

    // Perform the websocket handshake
    this->ws_.async_handshake(this->host_, "/",
        beast::bind_front_handler(
            &WebSocket::on_handshake,
            shared_from_this()
        )
    );
}

void WebSocket::on_handshake(beast::error_code ec)
{
    if (ec)
        return fail(ec, "handshake");

    if (this->_connectCallback != nullptr)
        this->_connectCallback();

    // Read a message into our buffer
    this->ws_.async_read(
        this->buffer_,
        beast::bind_front_handler(
            &WebSocket::on_read,
            shared_from_this()
        )
    );
}

void WebSocket::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");
}

void WebSocket::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "read");

    std::stringstream dataStream;
    dataStream << beast::make_printable(this->buffer_.data());
    std::string data = dataStream.str();

    if (this->_readCallback != nullptr)
        this->_readCallback(data);

    this->buffer_.clear();

    // Read a message into our buffer
    this->ws_.async_read(
        this->buffer_,
        beast::bind_front_handler(
            &WebSocket::on_read,
            shared_from_this()
        )
    );
}

void WebSocket::on_close(beast::error_code ec)
{
    if (ec)
        return fail(ec, "close");
}

void WebSocket::write(std::string text)
{
    // Send the message
    this->ws_.async_write(
        net::buffer(text),
        beast::bind_front_handler(
            &WebSocket::on_write,
            shared_from_this()
        )
    );
}

void WebSocket::close()
{
    // Close the WebSocket connection
    this->ws_.async_close(websocket::close_code::normal,
        beast::bind_front_handler(
            &WebSocket::on_close,
            shared_from_this()
        )
    );
}


void WebSocket::setReadCallback(read_callback readCallback)
{
    this->_readCallback = readCallback;
}