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
    std::unordered_set<std::shared_ptr<session>> clients;

public:
    server(io::io_context &io_context, std::uint16_t port)
            : io_context(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
    }

    void async_accept();

    void post(std::string const &message);
};


#endif //CHAT_APP_SERVER_H
