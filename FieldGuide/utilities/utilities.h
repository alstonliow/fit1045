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

double read_double(string prompt);

template <typename T>
bool is_negative(T value)
{
    return value < 0;
}

double read_non_negative_double(string prompt);

int read_non_negative_int(string prompt);

#endif