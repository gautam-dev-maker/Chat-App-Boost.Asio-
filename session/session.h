//
// Created by Gautam Agrawal on 07/01/21.
//

#ifndef CHAT_APP_SESSION_H
#define CHAT_APP_SESSION_H

#include <boost/asio.hpp>
#include <queue>

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;
using namespace std::placeholders;

using message_handler = std::function<void(std::string)>;
using error_handler = std::function<void()>;

class session : public std::enable_shared_from_this<session>
{

private:
    tcp::socket socket;
    io::streambuf streambuf;
    std::queue<std::string> outgoing;
    message_handler on_message;
    error_handler on_error;

    void async_read();

    void on_read(error_code error, std::size_t bytes_transferred);

    void async_write();

    void on_write(error_code error, std::size_t bytes_transferred);


public:
    session(tcp::socket &&socket)
            : socket(std::move(socket))
    {
    }

    void start(message_handler &&on_message, error_handler &&on_error);

    void post(std::string const &message);
};


#endif //CHAT_APP_SESSION_H
