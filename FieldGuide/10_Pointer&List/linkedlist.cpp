#include "splashkit.h"

/**
 * A node is a class that contains a pointer to the next node,
 * and a data value
 *
 * @tparam T the type of the data will be stored in the node
 */
template <typename T>
class node
{
public:
    // last node when next is nullptr
    node *next;
    // the value this node stores
    T data;
};

/**
 * Linked list is a class that contains a pointer to the first node,
 * and the last node
 *
 * @tparam T is type of data
 */
template <typename T>
class linked_list
{
public:
    // head of the chain, nullptr when the list is empty
    node<T> *first;
    // tail of the chain, kept so add_node does not have to walk the whole list
    node<T> *last;

    /**
     * Create an empty list
     */
    linked_list()
    {
        // no nodes yet, so there is no head and no tail
        first = nullptr;
        last = nullptr;
    }

    /**
     * Add new node to the end of the list
     *
     * @param data The data to add
     */
    node<T> *add_node(T data)
    {
        // declare a pointer for the new node (not yet pointing to valid memory)
        node<T> *new_node;
        // allocate a new node on the heap and store its address in new_node
        new_node = new node<T>();

        // fill in the new node's data
        new_node->data = data;
        // this node will be the new tail, so it has no next node yet
        new_node->next = nullptr;

        // case 1: list is currently empty
        if (first == nullptr)
        {
            // new node is both the first and last node
            first = new_node;
            last = new_node;
        }
        // case 2: list already has at least one node
        else
        {
            // link the current last node to the new node
            last->next = new_node;
            // update last to point to the new tail
            last = new_node;
        }

        return new_node;
    }

    /**
     * Find and return the node previous to 'target node'
     *
     * @param target_node
     */
    node<T> *find_previous_node(node<T> *target_node)
    {
        // the head has nothing before it, so there is no previous node
        if (target_node == first)
        {
            return nullptr;
        }

        // walk the list from the front, one node at a time
        node<T> *current = first;
        while (current != nullptr)
        {
            // if the node after current is the one we want, current is the answer
            if (current->next == target_node)
            {
                return current;
            }
            // step forward along the chain
            current = current->next;
        }

        // reached the end without finding target_node, so it isn't in this list
        throw string("find_previous_node search failed: node not in list.");
    }

    /**
     * Clear all node
     */
    void clear()
    {
        node<T> *current = first;
        while (current != nullptr)
        {
            // remember the next node BEFORE deleting current,
            // otherwise current->next is gone and we lose the rest of the list
            node<T> *next = current->next;
            // free the heap memory for this node
            delete current;
            // move on to the node we saved
            current = next;
        }
        // every node is gone, so the list is now empty
        first = nullptr;
        last = nullptr;
    }

    /**
     * remove the specific node from the list
     *
     * @param del_node
     */
    void remove(node<T> *del_node)
    {
        node<T> *previous_node = nullptr;

        // case 1: deleting the head, so the second node becomes the new first
        if (first == del_node)
        {
            first = del_node->next;
            // nothing points at del_node, so there is no previous node
            previous_node = nullptr;
        }
        // case 2: deleting a node in the middle or at the end
        else
        {
            // find the node that currently points to del_node
            previous_node = find_previous_node(del_node);
            // unlink del_node by pointing previous straight at del_node's next
            previous_node->next = del_node->next;
        }

        // if we removed the tail, the previous node becomes the new tail
        // (nullptr when the list is now empty)
        if (last == del_node)
        {
            last = previous_node;
        }

        // now that nothing points to it, free its heap memory
        delete del_node;
    }

    /**
     * Insert a node into a list, after the previous list
     *
     * @param in_node
     * @param previous_node
     */
    void insert(node<T> *in_node, node<T> *previous_node)
    {
        // the new node takes over whatever previous_node used to point at
        in_node->next = previous_node->next;
        // previous_node now points at the new node, splicing it into the chain
        previous_node->next = in_node;

        // if we inserted after the old tail, the new node is the new tail
        if (last == previous_node)
        {
            last = in_node;
        }
    }

    /**
     * Call func once for each value in the list, in order.
     * func takes the data by reference, so it can read or change it.
     *
     * @tparam F any callable (function pointer or lambda)
     * @param func the action to perform on every element
     */
    template <typename F>
    void visit(F func)
    {
        // start at the head and walk to the end
        node<T> *current = first;
        while (current != nullptr)
        {
            // hand this node's value to the caller's function
            func(current->data);
            // step forward along the chain
            current = current->next;
        }
    }

    /**
     * Combine every value in the list down to a single result.
     * func is called as func(running_value, data) and returns the new running value.
     *
     * @tparam R the type of the result being built up
     * @tparam F any callable (function pointer or lambda)
     * @param initial_value the starting value before any element is seen
     * @param func how to fold one element into the running value
     * @return the running value after the whole list has been folded in
     */
    template <typename R, typename F>
    R fold(R initial_value, F func)
    {
        // the running result, updated once per node
        R value = initial_value;

        // walk the list from the head
        node<T> *current = first;
        while (current != nullptr)
        {
            // fold this element into the running result
            value = func(value, current->data);
            current = current->next;
        }

        // an empty list just gives back the initial value
        return value;
    }
};

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