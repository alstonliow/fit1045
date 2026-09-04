#ifndef BOUNDED_ARRAY_HPP
#define BOUNDED_ARRAY_HPP

#include "splashkit.h"

// Thrown when an operation would push the array past MAX_CAPACITY
class array_full
{
};

// Thrown when an index is outside the range 0..length()-1
class array_invalid_index
{
};

// A fixed-capacity array of `T` that keeps track of how many
// elements are currently in use, and validates every index access.
template <typename T, int MAX_CAPACITY>
class bounded_array
{
    int size;             // number of elements currently stored
    T data[MAX_CAPACITY]; // storage - only the first `size` values are valid

public:
    // Create an empty array
    bounded_array()
    {
        size = 0;
    }

    // The number of elements currently stored
    int length()
    {
        return size;
    }

    // The most elements this array can ever hold
    int capacity()
    {
        return MAX_CAPACITY;
    }

    // Append `value` to the end of the array.
    // Throws array_full if the array is already at capacity.
    void add(T value)
    {
        if (size >= MAX_CAPACITY)
        {
            throw array_full();
        }
        data[size] = value;
        size++;
    }

    // Access the element at `index` by reference, so the caller can
    // both read and assign to it (e.g. numbers.get(2) = -8.5).
    // Throws array_invalid_index if the index is outside 0..size-1.
    T &get(int index)
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }
        return data[index];
    }

    // Read-only version of `get`, used when the array itself is const
    const T &get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }
        return data[index];
    }

    // Index syntax (numbers[2]) as a shorthand for get - same checks apply
    T &operator[](int index)
    {
        return get(index);
    }

    // Read-only index syntax, used when the array itself is const
    const T &operator[](int index) const
    {
        return get(index);
    }

    // Remove the element at `index`, shifting every later element
    // down one position to close the gap.
    // Throws array_invalid_index if the index is outside 0..size-1.
    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }
        // Shift each following element back over its predecessor
        for (int i = index + 1; i < size; i++)
        {
            data[i - 1] = data[i];
        }
        size--;
    }

    // Append `count` copies of `value` to the end of the array.
    // Throws array_full if there is not enough room for them all.
    void fill(int count, T value)
    {
        if (size + count > MAX_CAPACITY)
        {
            throw array_full();
        }
        for (int i = 0; i < count; i++)
        {
            add(value);
        }
    }
};

#endif