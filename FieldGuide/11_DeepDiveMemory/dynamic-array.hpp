#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "splashkit.h"
#include <cstdlib> // malloc, free
#include <new>     // placement new

// Thrown when malloc fails to allocate the requested memory
class allocation_failed
{
};

template <typename T>
class dynamic_array
{
    int size;     // number of constructed elements
    int capacity; // number of slots currently allocated
    T *data;      // raw, malloc'd storage - NOT all constructed

public:
    // Note: starts with room for 4 elements, none constructed yet
    dynamic_array()
    {
        size = 0;
        capacity = 4;
        data = (T *)malloc(capacity * sizeof(T));
        if (data == nullptr)
        {
            throw allocation_failed();
        }
    }

    // Disable copying - copying a dynamic_array would let two objects
    // share the same heap memory, leading to double free.
    dynamic_array(const dynamic_array &other) = delete;
    dynamic_array &operator=(const dynamic_array &other) = delete;

    ~dynamic_array()
    {
        // Only destruct the elements that were actually constructed
        for (int i = 0; i < size; i++)
        {
            data[i].~T();
        }
        free(data);
    }

    // Note: returns size (elements in use), not capacity
    int length() const
    {
        return size;
    }

    // Doubles capacity: allocates new raw memory, moves existing
    // elements across via placement new, destructs the old ones,
    // then frees the old block.
    void resize()
    {
        int new_capacity = capacity * 2;
        T *new_data = (T *)malloc(new_capacity * sizeof(T));
        if (new_data == nullptr)
        {
            throw allocation_failed();
        }

        for (int i = 0; i < size; i++)
        {
            new (&new_data[i]) T(data[i]); // placement new, copy-construct
            data[i].~T();                  // destruct the old element
        }

        free(data);
        data = new_data;
        capacity = new_capacity;
    }

    // Constructs a new element at data[size] using placement new
    void add(T value)
    {
        if (size >= capacity)
        {
            resize();
        }
        new (&data[size]) T(value);
        size++;
    }

    // Destructs the removed element, then shifts later elements down
    // Note: no bounds check - index must be in [0, size)
    void remove(int index)
    {
        data[index].~T();

        for (int i = index + 1; i < size; i++)
        {
            new (&data[i - 1]) T(data[i]);
            data[i].~T();
        }
        size--;
        // capacity is intentionally left unchanged
    }

    // Note: no bounds check - caller must ensure index < size
    T &get(int index)
    {
        return data[index];
    }

    const T &get(int index) const
    {
        return data[index];
    }

    // Note: [] just forwards to get(), so arr[i] works like an array
    T &operator[](int index)
    {
        return get(index);
    }

    const T &operator[](int index) const
    {
        return get(index);
    }
};

#endif