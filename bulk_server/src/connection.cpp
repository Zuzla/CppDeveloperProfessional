
#include <boost/asio.hpp>

#include <iostream>

#include "connection.h"

Connection::Connection(boost::asio::ip::tcp::socket &socket, std::shared_ptr<Bulk> &bulk) 
    : socket_(std::move(socket)),
      bulk_(bulk)
{   }

void Connection::listen()
{
    // pass "self" to the callback in order to keep the instance of Connection alive while the connection exists
    auto inputHandler = [this, self = shared_from_this()](boost::system::error_code error, std::size_t bytesTransferred)
    {
        if (error)
        {
            if (error != boost::asio::error::eof && error != boost::asio::error::connection_reset)
            {
                std::cerr << "Error reading incoming data. Code: " << error << " Message: " << error.message() << std::endl;
            }
        }
        else
        {
            if (bytesTransferred > 0)
            {
                std::string line(request.data(), bytesTransferred);
                try
                {
                    bulk_->AddCommand(line);
                }
                catch (std::exception &e)
                {
                    std::cerr << "Error parsing '" << line << "': " << e.what() << std::endl;
                }
            }

            listen();
        }
    };

    socket_.async_read_some(boost::asio::buffer(request, BLOCK_SIZE), inputHandler);
}