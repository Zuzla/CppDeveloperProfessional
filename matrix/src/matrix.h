#include <iostream>
#include <memory>
#include <map>

template <typename T>
class Matrix;

template <typename T>
class Row
{
public:
    Row(const std::shared_ptr<Matrix<T>> &matrix, int x) : _matrix(matrix)
    {
        _coordinates.first = x;
    }

    Row<T> &operator[](int y)
    {
        _coordinates.second = y;
        return *this;
    }

    Row<T> &operator=(const T& val)
    {
        _matrix->add(_coordinates, val);
        return *this;
    }

    operator T()
    {
        return _matrix->get_f(_coordinates);
    }

private:
    std::pair<int, int> _coordinates;
    std::shared_ptr<Matrix<T>> _matrix;
};

template <typename T>
class Matrix : public std::enable_shared_from_this<Matrix<T>>
{
public:
    const size_t size()  const noexcept
    {
        return _data.size();
    }

    auto begin() const noexcept
    {
        return _data.begin();
    }

    auto end() const noexcept
    {
        return _data.end();
    }

    std::shared_ptr<Matrix<T>> getptr()
    {
        return this->shared_from_this();
    }

    Row<T> operator[](int ind)
    {
        Row row(this->shared_from_this(), ind);
        return row;
    }

    void add(std::pair<int, int> coord, const T& value)
    {
        _data[coord] = value;
    }

    T get_f(const std::pair<int, int>& coord)
    {
        return _data[coord];
    }

private:
    std::map<std::pair<int, int>, T> _data;
};