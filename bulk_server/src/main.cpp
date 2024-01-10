
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <iostream>
#include <boost/asio.hpp>
#include "server.h"
#include "bulk.h"

namespace net = boost::asio;
namespace sys = boost::system;

using namespace std::literals;

int main()
{
    try
    {
        auto bulk = std::make_shared<Bulk>(3);

        net::io_context  ioc;
        Server server(ioc, 9000, bulk);

        // Подписываемся на сигналы и при их получении завершаем работу сервера
        net::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const sys::error_code &ec, [[maybe_unused]] int signal_number)
                           {
            if (!ec) {
                std::cout << "Signal "sv << signal_number << " received"sv << std::endl;
                ioc.stop();
            } });

        ioc.run(); // запускаем цикл обработки событий
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}