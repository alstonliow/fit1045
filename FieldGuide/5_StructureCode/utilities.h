#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using std::string;

/**
 * Read a string from user
 *
 * @param prompt the output message
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

#endif
