#include "session.h"


void session::async_read()
{
    io::async_read_until(socket, streambuf, "\n", std::bind(&session::on_read, shared_from_this(), _1, _2));
}

void session:: on_read(error_code error, std::size_t bytes_transferred)
{
    if (!error)
    {
        std::stringstream message;
        message << socket.remote_endpoint(error) << ": " << std::istream(&streambuf).rdbuf();
        streambuf.consume(bytes_transferred);
        on_message(message.str());
        async_read();
    }
    else
    {
        socket.close(error);
        on_error();
    }
}

void session::async_write()
{
    io::async_write(socket, io::buffer(outgoing.front()), std::bind(&session::on_write, shared_from_this(), _1, _2));
}

void session::on_write(error_code error, std::size_t bytes_transferred)
{
    if (!error)
    {
        outgoing.pop();

        if (!outgoing.empty())
        {
            async_write();
        }
    }
    else
    {
        socket.close(error);
        on_error();
    }
}


void session:: start(message_handler &&on_message, error_handler &&on_error)
{
    this->on_message = std::move(on_message);
    this->on_error = std::move(on_error);
    async_read();
}

void session::post(std::string const &message)
{
    bool idle = outgoing.empty();
    outgoing.push(message);

    if (idle)
    {
        async_write();
    }
}


