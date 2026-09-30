#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "splashkit.h"

// Grows automatically when capacity is reached (no MAX_CAPACITY template param)
template <typename T>
class dynamic_array
{
    int size;     // elements currently stored
    int capacity; // elements data can currently hold
    T *data;      // heap storage, resized as needed

public:
    // Allocates immediately on creation
    dynamic_array()
    {
        size = 0;
        capacity = 4;
        data = new T[capacity];
    }

    ~dynamic_array()
    {
        delete[] data;
    }

    int length() const
    {
        return size;
    }

    // Doubles capacity, copies old elements across
    void resize()
    {
        int new_capacity = capacity * 2;
        T *new_data = new T[new_capacity];

        for (int i = 0; i < size; i++)
        {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    // Resizes instead of throwing when full
    void add(T value)
    {
        if (size >= capacity)
        {
            resize();
        }
        data[size] = value;
        size++;
    }

    // Capacity never shrinks here
    void remove(int index)
    {
        for (int i = index + 1; i < size; i++)
        {
            data[i - 1] = data[i];
        }
        size--;
    }

    T &get(int index)
    {
        return data[index];
    }

    const T &get(int index) const
    {
        return data[index];
    }

    T &operator[](int index)
    {
        return get(index);
    }

    const T &operator[](int index) const
    {
        return get(index);
    }

    // No copy constructor: copying does a shallow pointer copy,
    // leading to double delete when both objects are destroyed
};

#endif