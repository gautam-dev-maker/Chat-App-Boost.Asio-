#include "server/server.h"

namespace io = boost::asio;

int main()
{
    io::io_context io_context;
    server srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}