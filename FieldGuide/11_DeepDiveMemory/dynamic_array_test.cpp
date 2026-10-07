#include "splashkit.h"
#include "dynamic-array.hpp"
#include <cassert>

int alive = 0; // number of live counted objects, used to test the destructor

struct counted
{
    counted() { alive++; }
    counted(const counted &) { alive++; }
    ~counted() { alive--; }
};

void test_constructor()
{
    dynamic_array<int> arr;
    assert(arr.length() == 0);
    assert(arr.get_capacity() == 4);
}

void test_length()
{
    dynamic_array<int> arr;
    assert(arr.length() == 0);
    arr.add(1);
    arr.add(2);
    assert(arr.length() == 2);
    arr.remove(0);
    assert(arr.length() == 1);
}

void test_get_capacity()
{
    dynamic_array<int> arr;
    assert(arr.get_capacity() == 4);
    for (int i = 0; i < 4; i++)
    {
        arr.add(i);
    }
    assert(arr.get_capacity() == 4); // exactly full, no resize yet
    arr.add(4);
    assert(arr.get_capacity() == 8); // doubles only when exceeded
}

void test_add()
{
    dynamic_array<int> arr;
    arr.add(5);
    assert(arr.length() == 1);
    assert(arr[0] == 5);

    for (int i = 1; i < 5; i++) // triggers a resize
    {
        arr.add(i * 10);
    }
    assert(arr.length() == 5);
    assert(arr[0] == 5);  // old value survives resize
    assert(arr[4] == 40); // new value is correct
}

void test_add_string()
{
    dynamic_array<string> words;
    for (int i = 0; i < 9; i++) // spans two resizes
    {
        words.add("w" + to_string(i));
    }
    assert(words.length() == 9);
    assert(words[0] == "w0");
    assert(words[8] == "w8");
}

void test_resize()
{
    dynamic_array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.resize();
    assert(arr.get_capacity() == 8);
    assert(arr.length() == 2); // length unchanged
    assert(arr[0] == 1);       // values unchanged
    assert(arr[1] == 2);
}

void test_remove()
{
    dynamic_array<int> arr;
    for (int i = 0; i < 5; i++)
    {
        arr.add(i * 10); // [0 10 20 30 40]
    }

    arr.remove(1); // middle
    assert(arr.length() == 4);
    assert(arr[0] == 0);
    assert(arr[1] == 20);
    assert(arr[3] == 40);

    arr.remove(0); // first
    assert(arr.length() == 3);
    assert(arr[0] == 20);

    arr.remove(2); // last
    assert(arr.length() == 2);
    assert(arr[1] == 30);

    assert(arr.get_capacity() == 8); // remove does not change capacity
}

void test_get()
{
    dynamic_array<int> arr;
    arr.add(10);
    arr.add(20);
    assert(arr.get(0) == 10);
    assert(arr.get(1) == 20);

    arr.get(0) = 99; // returns a reference, so it is writable
    assert(arr.get(0) == 99);

    const dynamic_array<int> &c = arr; // const version
    assert(c.get(1) == 20);
}

void test_operator_index()
{
    dynamic_array<int> arr;
    arr.add(10);
    arr.add(20);
    assert(arr[0] == 10);
    assert(arr[1] == 20);

    arr[1] = 77; // writable
    assert(arr[1] == 77);

    const dynamic_array<int> &c = arr; // const version
    assert(c[0] == 10);
}

void test_destructor()
{
    {
        dynamic_array<counted> objs;
        for (int i = 0; i < 5; i++) // triggers a resize
        {
            objs.add(counted());
        }
        assert(alive == 5); // resize neither duplicates nor leaks objects
        objs.remove(0);
        assert(alive == 4); // remove destructs the removed element
    }
    assert(alive == 0); // array destructor destructs all remaining elements
}

void test_get_out_of_range()
{
    dynamic_array<int> arr;
    arr.add(1);

    try
    {
        arr.get(1); // index == length
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }

    try
    {
        arr.get(-1); // negative index
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }

    dynamic_array<int> empty;
    try
    {
        empty.get(0); // empty array
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }

    const dynamic_array<int> &c = arr;
    try
    {
        c.get(1); // const version
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }
}

void test_remove_out_of_range()
{
    dynamic_array<int> arr;
    arr.add(1);

    try
    {
        arr.remove(1); // index == length
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }

    try
    {
        arr.remove(-1); // negative index
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }

    assert(arr.length() == 1); // array is intact after the exceptions
}

void test_operator_index_out_of_range()
{
    dynamic_array<int> arr;
    arr.add(1);

    try
    {
        arr[1]; // index == length
        assert(false);
    }
    catch (index_out_of_range)
    {
        assert(true);
    }
}

int main()
{
    test_constructor();
    test_length();
    test_get_capacity();
    test_add();
    test_add_string();
    test_resize();
    test_remove();
    test_get();
    test_operator_index();
    test_destructor();
    test_get_out_of_range();
    test_remove_out_of_range();
    test_operator_index_out_of_range();

    write_line("ALL PASSED");
}