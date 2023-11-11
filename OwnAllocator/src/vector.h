#include <algorithm>
#include <iostream>

template <typename T, class Alloc = std::allocator<T>>
class vector
{
public:
    vector() = default;

    vector(const vector &other)
        : data(other.capacity_ == 0
                   ? nullptr
                   : allocation.allocate(other.capacity_ * sizeof(T))),
          size_(other.size_), capacity_(other.capacity_)
    {
        try
        {
            // memcpy(tmp_data, data, sizeof(T) * size_);
            for (size_t i = 0; i < size_; ++i)
            {
                data[i] = other.data[i];
            }
        }
        catch (...)
        {
            allocation.deallocate(data);
            throw;
        }
    }

    vector &operator=(const vector &other)
    {
        if (this != other)
        {
            vector temp(other);
            swap(temp);
        }
        return *this;
    }

    vector &operator=(vector &&other)
    {
        if (this != other)
        {
            swap(other);
        }
        return *this;
    }

    vector(vector &&other)
        : data(other.capacity_ == 0
                   ? nullptr
                   : allocation.allocate(other.capacity_ * sizeof(T))),
          size_(other.size_), capacity_(other.capacity_)
    {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    void push_back(const T &value)
    {
        T temp(value);
        push_back(std::move(temp));
    }

    void push_back(T &&value)
    {
        if (size_ == capacity_)
        {
            capacity_ = std::max(capacity_ * 2, 16lu);

            T *tmp_data = nullptr;
            try
            {
                tmp_data = allocation.allocate(capacity_ * sizeof(T));
                // memcpy(tmp_data, data, sizeof(T) * size_);
                for (size_t i = 0; i < size_; ++i)
                {
                    tmp_data[i] = data[i];
                }
            }
            catch (...)
            {
                allocation.deallocate(data);
                throw;
            }

            if (data != nullptr)
                destroy();

            data = tmp_data;
        }

        data[size_++] = value;
    }

    void pop_back()
    {
        if (size_ == 0)
            throw std::range_error("vector is empty!");

        data[size--]->~T();
    }

    void swap(vector &other)
    {
        using std::swap;
        swap(data, other.data);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

    const size_t size() const noexcept { return size_; }

    const bool empty() const noexcept { return size_ == 0u; }

    void reserv(size_t new_capacity) {}

    T operator[](size_t num)
    {
        if (num > size_)
            throw std::range_error("size error");

        return data[num];
    }

private:
    void destroy()
    {
        for (size_t i = 0; i < size_; i++)
        {
            data[i].~T();
        }

        allocation.deallocate(data);
    }

private:
    T *data = nullptr;
    size_t size_ = 0u;
    size_t capacity_ = 0u;

    Alloc allocation;
};