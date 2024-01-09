#include "async.h"
#include <iostream>
#include <memory>

namespace async
{

    handle_t connect(std::size_t bulk)
    {
        return new Bulk(bulk);
    }

    void receive(handle_t handle, const char *data, std::size_t size)
    {
        auto controller = static_cast<Bulk *>(handle);
        if (handle == nullptr)
            return;

        controller->AddCommand(std::string{data, size});
    }

    void disconnect(handle_t handle)
    {
        auto controller = static_cast<Bulk *>(handle);
        if (handle == nullptr)
            return;

        controller->Log();

        delete controller;
    }

}
