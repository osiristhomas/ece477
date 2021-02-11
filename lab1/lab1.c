/* Osiris Thomas
 * ECE 477 Lab 1
 * Prints the size of variable types in bytes
 */

#include <stdio.h>
#include <limits.h>

int main(void)
{
	// size of variable types
	printf("Size of char: %d bytes\n", sizeof(char));
	printf("Size of short: %d bytes\n", sizeof(short));
	printf("Size of int: %d bytes\n", sizeof(int));
	printf("Size of long: %d bytes\n", sizeof(long));
	printf("Size of float: %d bytes\n", sizeof(float));
	printf("Size of double: %d bytes\n", sizeof(double));

	// values of constants
	printf("INT_MAX - decimal: %d hex: %X \n", INT_MAX, INT_MAX);
	printf("UINT_MAX - decimal: %u hex: %X \n", UINT_MAX, UINT_MAX);
	printf("LONG_MAX - decimal: %d hex: %X \n", LONG_MAX, LONG_MAX);
	printf("ULONG_MAX - decimal: %u hex: %X \n", ULONG_MAX, ULONG_MAX);

	return 0;

}
