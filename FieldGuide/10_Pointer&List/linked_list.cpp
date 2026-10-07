#include "splashkit.h"
#include "list.hpp"
#include <cassert>

// Builds a string of all elements, e.g. "2 4 8 "
string contents(linked_list<int> &list)
{
    return list.fold(string(""), [](string acc, const int &d)
                     { return acc + to_string(d) + " "; });
}

void test_constructor()
{
    linked_list<int> list;
    assert(list.first == nullptr);
    assert(list.last == nullptr);
    assert(contents(list) == ""); // empty list has no elements
}

void test_add_node()
{
    linked_list<int> list;

    node<int> *a = list.add_node(2); // first node
    assert(list.first == a);
    assert(list.last == a);
    assert(a->data == 2);
    assert(a->next == nullptr);

    node<int> *b = list.add_node(4);
    node<int> *c = list.add_node(8);
    assert(contents(list) == "2 4 8 "); // added in order
    assert(list.first == a);            // first unchanged
    assert(list.last == c);             // last updated
    assert(c->next == nullptr);         // tail points to nothing
    assert(b->data == 4);
}

void test_find_previous_node()
{
    linked_list<int> list;
    node<int> *a = list.add_node(2);
    node<int> *b = list.add_node(4);
    node<int> *c = list.add_node(8);

    assert(list.find_previous_node(a) == nullptr); // head has no previous
    assert(list.find_previous_node(b) == a);       // middle
    assert(list.find_previous_node(c) == b);       // tail
}

void test_insert()
{
    linked_list<int> list;
    node<int> *a = list.add_node(2);
    node<int> *b = list.add_node(4);

    node<int> *five = new node<int>(); // insert in the middle
    five->data = 5;
    five->next = nullptr;
    list.insert(five, a);
    assert(contents(list) == "2 5 4 ");
    assert(a->next == five);
    assert(five->next == b);

    node<int> *nine = new node<int>(); // insert after the tail
    nine->data = 9;
    nine->next = nullptr;
    list.insert(nine, b);
    assert(contents(list) == "2 5 4 9 ");
    assert(list.last == nine); // last is updated
}

void test_remove()
{
    linked_list<int> list;
    node<int> *a = list.add_node(2);
    node<int> *b = list.add_node(4);
    node<int> *c = list.add_node(8);
    node<int> *d = list.add_node(16);

    list.remove(b); // middle
    assert(contents(list) == "2 8 16 ");
    assert(a->next == c);

    list.remove(d); // last
    assert(contents(list) == "2 8 ");
    assert(list.last == c);
    assert(c->next == nullptr);

    list.remove(a); // first
    assert(contents(list) == "8 ");
    assert(list.first == c);

    list.remove(c); // only node left
    assert(list.first == nullptr);
    assert(list.last == nullptr);
    assert(contents(list) == "");
}

void test_visit()
{
    linked_list<int> list;
    list.add_node(4);
    list.add_node(6);

    list.visit([](int &d)
               { d *= 10; });
    assert(contents(list) == "40 60 "); // every element modified

    linked_list<int> empty;
    empty.visit([](int &d)
                { d = 99; });
    assert(contents(empty) == ""); // visiting an empty list does nothing
}

void test_fold()
{
    linked_list<int> list;
    list.add_node(40);
    list.add_node(60);

    assert(list.fold(0, [](int acc, const int &d)
                     { return acc + d; }) == 100); // sum
    assert(list.fold(true, [](bool acc, const int &d)
                     { return acc && d > 50; }) == false); // all > 50
    assert(list.fold(true, [](bool acc, const int &d)
                     { return acc && d > 10; }) == true); // all > 10

    linked_list<int> empty;
    assert(empty.fold(7, [](int acc, const int &d)
                      { return acc + d; }) == 7); // empty list returns the initial value
}

void test_clear()
{
    linked_list<int> list;
    list.add_node(1);
    list.add_node(2);
    list.add_node(3);

    list.clear();
    assert(list.first == nullptr);
    assert(list.last == nullptr);
    assert(contents(list) == "");

    list.add_node(5); // list is still usable after clear
    assert(contents(list) == "5 ");

    linked_list<int> empty;
    empty.clear(); // clearing an empty list is safe
    assert(empty.first == nullptr);
}

void test_find_previous_node_not_found()
{
    linked_list<int> list;
    list.add_node(2);

    node<int> stray; // not in the list
    stray.data = 0;
    stray.next = nullptr;

    try
    {
        list.find_previous_node(&stray);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_remove_not_found()
{
    linked_list<int> list;
    list.add_node(2);
    list.add_node(4);

    node<int> stray; // not in the list
    stray.data = 0;
    stray.next = nullptr;

    try
    {
        list.remove(&stray);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }

    assert(contents(list) == "2 4 "); // list is intact after the exception
}

int main()
{
    test_constructor();
    test_add_node();
    test_find_previous_node();
    test_insert();
    test_remove();
    test_visit();
    test_fold();
    test_clear();
    test_find_previous_node_not_found();
    test_remove_not_found();

    write_line("ALL PASSED");
}