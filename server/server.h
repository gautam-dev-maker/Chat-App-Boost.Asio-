#ifndef CHAT_APP_SERVER_H
#define CHAT_APP_SERVER_H

#include <unordered_set>
#include "../session/session.h"

namespace io = boost::asio;

class server
{
private:
    io::io_context &io_context;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
    std::unordered_set<std::shared_ptr<session>> clients; // A set of connected clients

public:
    server(io::io_context &io_context, std::uint16_t port)
            : io_context(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
    }

    // async_accept function greets a newcomer personally and introduces him to the others.
    void async_accept();

    // post function broadcasts a message to all clients connected. This function is also used as a client's message handler
    void post(std::string const &message);
};


#endif //CHAT_APP_SERVER_H
