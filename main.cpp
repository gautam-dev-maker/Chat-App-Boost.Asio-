#include "server/server.h"

namespace io = boost::asio;

using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;

int main()
{
    io::io_context io_context;
    server srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}