#include <iostream>
#include <memory>

template <class T, std::size_t growSize = 1024>
class MemoryPool
{
    struct Block
    {
        Block *next;
    };

    class Buffer
    {
        static const std::size_t blockSize = sizeof(T) > sizeof(Block) ? sizeof(T) : sizeof(Block);
        uint8_t data[blockSize * growSize];

    public:
        Buffer *const next;

        Buffer(Buffer *next) : next(next)
        {
        }

        T *getBlock(std::size_t index)
        {
            return reinterpret_cast<T *>(&data[blockSize * index]);
        }
    };

    Block *firstFreeBlock = nullptr;
    Buffer *firstBuffer = nullptr;
    std::size_t bufferedBlocks = growSize;

public:

    ~MemoryPool()
    {
        while (firstBuffer)
        {
            Buffer *buffer = firstBuffer;
            firstBuffer = buffer->next;
            delete buffer;
        }
    }

    T *allocate()
    {
        if (firstFreeBlock)
        {
            Block *block = firstFreeBlock;
            firstFreeBlock = block->next;
            return reinterpret_cast<T *>(block);
        }

        if (bufferedBlocks >= growSize)
        {
            firstBuffer = new Buffer(firstBuffer);
            bufferedBlocks = 0;
        }

        return firstBuffer->getBlock(bufferedBlocks++);
    }

    void deallocate(T *pointer)
    {
        Block *block = reinterpret_cast<Block *>(pointer);
        block->next = firstFreeBlock;
        firstFreeBlock = block;
    }
};

template <class T, std::size_t growSize = 1024>
class Allocator : private MemoryPool<T, growSize>
{
public:
    using value_type = T;

    Allocator() = default;

    template <class U>
    Allocator(const Allocator<U> &) noexcept {}

    T *allocate(size_t size)
    {
        // return reinterpret_cast<T*>(::operator new(sizeof(T) * size));
        return MemoryPool<T, growSize>::allocate();
    };

    void deallocate(T *ptr, size_t size = sizeof(T))
    {
        //::operator delete(ptr);
        MemoryPool<T, growSize>::deallocate(ptr);
    };

    template <class Up, class... Args>
    void construct(Up *ptr, Args &&...args)
    {
        ::new (reinterpret_cast<void *>(ptr)) Up{std::forward<Args>(args)...};
    }

    void destroy(T *ptr)
    {
        ptr->~T();
    };

    template <class U>
    struct rebind
    {
        using other = Allocator<U, growSize>;
    };
};

template <typename T, typename U>
const bool operator==(const Allocator<T> &t, const Allocator<U> &u) noexcept
{
    return true;
}

template <typename T, typename U>
const bool operator!=(const Allocator<T> &t, const Allocator<U> &u) noexcept
{
    return false;
}