/* Osiris Thomas
 * ECE 477 Lab 1
 * Prints the size of variable types in bytes
 * 
 * Cool thing: determines the largest values that can be stored in different
 * sized ints
 */

#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

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

	// prints largest values of different int types
	uint8_t e = -1;
	uint16_t st = -1;
	uint32_t tt = -1;
	uint64_t sf = -1;

	printf("Max uint8_t number: %u\n", e); 
	printf("Max uint16_t number: %u\n", st); 
	printf("Max uint32_t number: %u\n", tt);
	// need a different way of printing a bit byte number 
	printf("Max uint64_t number: %"PRIu64"\n", sf); 

	return 0;
}
