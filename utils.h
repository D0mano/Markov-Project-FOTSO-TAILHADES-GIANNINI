#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * @brief Convert an integer into the associated string
 * @param num The integer to be converted
 * @return The associated string
 */
char *getID(int num);

/**
 * @brief Calculate the minimum of two integers
 * @param a The first integer
 * @param b The second integer
 * @return The smaller value between a and b
 */
int min(int a, int b);


/**
 * @brief Convert a class string into its corresponding letter representation.
 *
 * This function analyzes the provided string and returns a character
 * representing the associated class. The exact mapping depends on the
 * implementation logic (e.g., mapping full words or codes to a single letter).
 *
 * @param str A null-terminated string representing a class descriptor.
 * @return A character representing the class. If the string is invalid or
 *         unmapped, the function may return a default or error indicator.
 */
char class_to_letter(const char* str);

/**
 * @brief Compute the greatest common divisor (GCD) of multiple integers.
 *
 * This function calculates the GCD of an array of integers using the standard
 * iterative GCD reduction process. All provided values should be valid
 * integers; behavior with zero or negative values depends on implementation.
 *
 * @param vals An array of integers for which the GCD will be computed.
 * @param nbvals The number of integers contained in the array.
 * @return The greatest common divisor of all provided values. If nbvals is 0,
 *         the function may return 0 or an undefined value depending on the
 *         implementation.
 */
int gcd(int* vals,int nbvals);

#endif