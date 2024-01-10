
#include <iostream>
#include <memory>

#include <boost/asio.hpp>

#include "server.h"

using namespace boost::asio::ip;

Server::Server(boost::asio::io_context &ioContext_, size_t port_, std::shared_ptr<Bulk> &bulk)
    : _bulk(bulk),
      acceptor(ioContext_, tcp::endpoint(tcp::v4(), port_))
{

    accept();
}

void Server::accept()
{
    acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket)
                          {
                              if (error)
                              {
                                  std::cerr << "Error accepting request. Code: " << error << " Message: " << error.message() << std::endl;
                              }
                              else
                              {
                                  // Make a shared pointer in order to allow usage enable_shared_from_this in Connection.
                                  // The instance of Connection won't be deleted when "accept()" returns control because
                                  // the pointer to it will be "captured" in Connection::listen().
                                  std::make_shared<Connection>(socket, _bulk)->listen();

                                  // start listening for a next incoming connection
                                  accept();
                              } });
}