#ifndef CHEESE_SHOP_H
#define CHEESE_SHOP_H

#include "splashkit.h"
#include "splashkit-arrays.h"

/**
 * Data about a cheese within the order or in a stock
 *
 * @field name The name of cheese
 * @field weight The weight of cheese in kg
 * @field price The price of cheese per kg in cents
 */
struct cheese_data
{
    string name;
    double weight;
    int price;
};

/**
 * Data about the cheese shop
 *
 * @field cheese The list of cheese in shop
 */
struct shop_data
{
    dynamic_array<cheese_data> cheeses;
};

/**
 * Initialise a cheese_data value with the given name, weight and price.
 *
 * @param name The name of the cheese. Defaults to an empty string.
 * @param weight The weight of the cheese in kg. Defaults to 0.0.
 * @param price The price of the cheese per kg in cents. Defaults to 0.
 * @return cheese_data The initialised cheese value.
 */
cheese_data
new_cheese(string name = "", double weight = 0.0, int price = 0);

/**
 * Convert the cheese_data value to a string
 *
 * @param cheese The cheese_data value to convert
 * @param full_details If true, include all details of the cheese. Defaults to false
 * @return string The string representation of the cheese_data value
 */
string cheese_to_string(const cheese_data &cheese, bool full_details = false);

/**
 * Calculate total cost of the cheese
 *
 * @param cheese The cheese data
 * @return int The total cost in cents
 */
int total_cost(const cheese_data &cheese);

/**
 * Calculate the amount of cheese to be reduce without negative
 *
 * @param cheese cheese data
 * @param amount amount of cheese to be reduce
 */
double reduce_weight(cheese_data &cheese, double amount);

/**
 *Amount of cheese to be increse without negative

 @param cheese
 @param amount amount of incresing of cheese
 */
void increase_weight(cheese_data &cheese, double amount);

/**
 * adds the cheese to the end of our dynamic array
 *
 * @param shop The array
 * @param new_cheese The cheese data to add
 */
void add_cheese(shop_data &shop, const cheese_data &new_cheese);

/**
 * Return false when name is empty or price/weight is negative
 * print error message when false
 *
 * @param cheese cheese data
 * @param error_message error message to print
 * @return true if the cheese is valid, otherwise false
 */
bool cheese_valid(const cheese_data &cheese, string &error_message);

/**
 * Delete the cheese fron shop
 * 
 * @param shop 
 * @param index The index of cheese in the shop to be delete
 */
void delete_cheese(shop_data &shop, int index);

#endif