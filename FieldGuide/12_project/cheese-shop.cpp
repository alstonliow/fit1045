#include "cheese-shop.h"
#include <format>
#include <cmath>
#include <string>

using std::format;

cheese_data new_cheese(string name, double weight, int price)
{
    cheese_data cheese;
    cheese.name = name;
    cheese.weight = weight;
    cheese.price = price;
    return cheese;
}

int total_cost(const cheese_data &cheese)
{
    return round(cheese.weight * cheese.price);
}

string cheese_to_string(const cheese_data &cheese, bool full_details)
{
    if (full_details)
    {
        return format("{}: {:.2f} kg, ${:.2f}, total ${:.2f}",
                      cheese.name, cheese.weight, cheese.price / 100.0, total_cost(cheese) / 100.0);
    }
    else
    {
        return cheese.name;
    }
}

double reduce_weight(cheese_data &cheese, double amount)
{
    if (amount <= 0)
    {
        return 0;
    }
    if (amount >= cheese.weight)
    {
        double removed = cheese.weight;
        cheese.weight = 0;
        return removed;
    }

    cheese.weight -= amount;
    return amount;
}

void increase_weight(cheese_data &cheese, double amount)
{
    if (amount <= 0)
    {
        return;
    }
    else
    {
        cheese.weight += amount;
    }
}

void add_cheese(shop_data &shop, const cheese_data &new_cheese)
{
    shop.cheeses.add(new_cheese);
}