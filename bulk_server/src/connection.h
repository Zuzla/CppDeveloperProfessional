#pragma once

#include <boost/asio.hpp>

#include <iostream>

#include "bulk.h"
/**
 * Receives commands from a client.
 *
 * The connection stays open until the client breaks it.
 */
class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(boost::asio::ip::tcp::socket &socket, std::shared_ptr<Bulk> &bulk);

    void listen();

private:
    static constexpr std::uint8_t BLOCK_SIZE = 255;

    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<Bulk> bulk_;

    std::array<char, BLOCK_SIZE> request;
};