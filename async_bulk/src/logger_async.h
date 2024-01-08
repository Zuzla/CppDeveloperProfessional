#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <condition_variable>

#include "log.h"

using namespace std::chrono_literals;

// https://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
// https://www.geeksforgeeks.org/cpp-multithreading-condition-variables/

template <typename T>
class ConcurentQueue : public Logger
{
public:
    ConcurentQueue(size_t threads_count = 1) : _threads_count(threads_count)
    {
        if (_threads_count == 0)
            _threads_count = 1;

        /*
        shared переделать на unique
        ошибка при передаче параметра при unique_ptr - no known conversion for argument 1 from ‘[some_class]' to ‘[some_class]&&’
        */
        auto lm = [this, log = std::make_shared<T>()]()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(_mutex);

                _cv.wait(lock, [this]()
                         { return _queue.size() > 0; });

                auto data = _queue.front();
                if (data.data == "EOF")
                    break;

                log->Log(data);
                _queue.pop();

                std::this_thread::sleep_for(10ms);
            }
        };

        for (size_t i = 0; i < _threads_count; i++)
        {
            _threads.emplace_back(lm);
        }
    }

    void Log(const DataBclock &block) override
    {
        std::lock_guard{_mutex};
        _queue.push(block);
        _cv.notify_all();
    }

    ~ConcurentQueue()
    {
        for (auto &&t : _threads)
        {
            t.request_stop();
        }
        _cv.notify_all();
    }

private:
    std::queue<DataBclock> _queue;

    std::mutex _mutex;
    std::condition_variable _cv;

    size_t _threads_count;
    std::vector<std::jthread> _threads;
};