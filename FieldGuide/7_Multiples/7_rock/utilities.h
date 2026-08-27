#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using std::string;

/**
 * Read a string from user
 *
 * @param prompt
 * @returns the string entered
 */

string read_string(string prompt);

/**
 * Read an integer from user
 *
 * @param prompt message
 * @returns integer
 */

int read_integer(string prompt);

/**
 * Read an integer from user, within a given range
 *
 * @param prompt message
 * @param low    lowest num
 * @param high   largest num
 * @returns integer between low and high (include)
 */

int read_integer(string prompt, int low, int high);

/**
 * Read a double from user
 *
 * @param prompt message
 * @returns the value entered as a double
 */

double read_double(string prompt);

/**
 * Check if an integer is below zero
 *
 * @param value the number to test
 * @returns true when value is negative
 */

bool is_negative(int value);

/**
 * Check if a double is below zero
 *
 * @param value the number to test
 * @returns true when value is negative
 */

bool is_negative(double value);

/**
 * Read a double from user, repeating until it is zero or above
 *
 * @param prompt message
 * @returns a double that is not negative
 */

double read_non_negative_double(string prompt);

/**
 * Read an integer from user, repeating until it is zero or above
 *
 * @param prompt message
 * @returns an integer that is not negative
 */

int read_non_negative_int(string prompt);

#endif