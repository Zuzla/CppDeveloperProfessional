#pragma once

#include <boost/asio.hpp>

#include <iostream>
#include <memory>
#include <stdint.h>

#include "bulk.h"
#include "connection.h"

class Server
{
public:
    Server(boost::asio::io_context &ioContext_, size_t port_, std::shared_ptr<Bulk> &bulk);

private:
    std::shared_ptr<Bulk> _bulk;
    boost::asio::ip::tcp::acceptor acceptor;

    void accept();
};