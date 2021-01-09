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

    // async_read function reads a data from the remote client into the streambuf
    void async_read();

    // read handler formats a message from the client, passes it into the message handler, and starts receiving the next message right away.
    void on_read(error_code error, std::size_t bytes_transferred);

    // async_write function sends the front message from the message queue to the remote client
    void async_write();

    // The write handler pops the front message from the queue, and if the queue is still not empty, then it repeat sending messages right away
    void on_write(error_code error, std::size_t bytes_transferred);


public:
    session(tcp::socket &&socket)
            : socket(std::move(socket))
    {
    }

    // The start function now accept event handlers
    void start(message_handler &&on_message, error_handler &&on_error);

    // The post function enqueues a message addressed to the client and starts sending the message
    void post(std::string const &message);
};


#endif //CHAT_APP_SESSION_H
