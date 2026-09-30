#include "splashkit.h"
#include "list.hpp"

/**
 * Print one value followed by a space, for use with visit
 *
 * @param data the value to print
 */
void print_data(int &data)
{
    write(data);
    write(" ");
}

/**
 * Print every value in the list on one line
 *
 * @param list the list to print
 */
template <typename T>
void print_list(linked_list<T> &list)
{
    write("[ ");
    list.visit(print_data);
    write_line("]");
}

int main()
{
    linked_list<int> list;

    // ---- Test first node ----
    node<int> *first_node = list.add_node(2);

    write("This should be 2: ");
    write_line(list.first->data);

    write("This should also be 2: ");
    write_line(first_node->data);

    write("This should also be 2: ");
    write_line(list.last->data);

    // ---- Test adding more nodes ----
    list.add_node(4);
    list.add_node(8);
    list.add_node(16);

    write("This should be 4: ");
    write_line(list.first->next->data);

    write("This should be 8: ");
    write_line(list.first->next->next->data);

    write("This should be 16: ");
    write_line(list.last->data);

    // ---- Test find_previous_node ----
    node<int> *node_a = list.add_node(9);
    node<int> *node_b = list.add_node(18);

    if (list.find_previous_node(node_b) == node_a)
    {
        write_line("Found the correct previous node");
    }
    else
    {
        write_line("Found the wrong previous node");
    }

    // ---- Test insert ----
    // insert 5 between 4 and 8
    node<int> *node_five = new node<int>();
    node_five->data = 5;
    node_five->next = nullptr;
    list.insert(node_five, list.first->next);

    write("After inserting 5, should be [ 2 4 5 8 16 9 18 ]: ");
    print_list(list);

    // ---- Test remove ----
    list.remove(node_five);
    write("After removing 5, should be [ 2 4 8 16 9 18 ]: ");
    print_list(list);

    // ---- Test visit with a named function ----
    write("Visit with print_data, should be [ 2 4 8 16 9 18 ]: ");
    print_list(list);

    // ---- Test visit with a non-capturing lambda ----
    write("Multiply all by 10, should be [ 20 40 80 160 90 180 ]: ");
    list.visit([](int &data)
               { data *= 10; });
    print_list(list);

    // ---- Test fold with a named function ----
    int product_check = list.fold(0, [](int acc, const int &data)
                                  { return acc + data; });
    write_line("Sum after multiplying by 10, should be 570: " + to_string(product_check));

    // ---- Test fold checking all positive ----
    bool all_positive = list.fold(true, [](bool acc, const int &data)
                                  { return acc && (data > 0); });
    write_line(all_positive ? "All Positive" : "Not All Positive");

    // ---- Test visit with a capturing lambda ----
    // list is [ 20 40 80 160 90 180 ] at this point
    int total_sum = 0;
    list.visit([&total_sum](int &data)
               { total_sum += data; });
    write_line("Sum via capturing visit, should be 570: " + to_string(total_sum));

    // ---- Test fold reusing a captured multiplier ----
    int multiplier = 3;
    int scaled_sum = list.fold(0, [multiplier](int acc, const int &data)
                               { return acc + data * multiplier; });
    write_line("Sum of (each element * 3), should be 1710: " + to_string(scaled_sum));

    // ---- Test clear ----
    list.clear();
    write("After clear, should be [ ]: ");
    print_list(list);

    if (list.first == nullptr && list.last == nullptr)
    {
        write_line("first and last correctly reset to nullptr");
    }
    else
    {
        write_line("first/last not properly reset");
    }

    // ---- Test fold on an empty list gives back the initial value ----
    int empty_sum = list.fold(0, [](int acc, const int &data)
                              { return acc + data; });
    write_line("Sum of the empty list, should be 0: " + to_string(empty_sum));
}