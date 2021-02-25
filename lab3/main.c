/* Osiris Thomas
 * main.c
 * ECE 477 Lab 3
 * Displays the cpu load on 8 leds
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "led.h"

// initializes all useable GPIO pins
void init_gpio(const char **);
// unexports all used GPIO pins
void stop_gpio(const char **);
// set leds based on user input
void set_leds(const char **, int);

int main(int argc, char *argv[])
{
	// number in argv[1]
	long input;
	// "trashcan" for the string part of 
	char *buf;
	// checks for correct input
	if (argc != 2) {
		printf("Must enter one argument\n");
		exit(1);
	} 
	
	// converts input string (hex, dec, oct) to int
	input = strtol(argv[1], &buf, 0);
	printf("Entered input: %ld\n", input);
	if (input < 0 || input > 0xFF) {
		printf("Input must be between 0 and 255/0xFF/0377\n");
		exit(2);
	}
	
	const char *gpio[8] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	init_gpio(gpio);
	//printf("Succesfully initialized GPIO\n");	
	
	set_leds(gpio, input);	
	
	stop_gpio(gpio);
	return 0; 
}

// initializes all useable GPIO pins
void init_gpio(const char **gpio)
{
	char pin[3];
	int i;
	for (i = 0; i < 8; i++) {
		strcpy(pin, gpio[i]);
		//printf("Initializing GPIO %s\n", pin);
		exportpin(pin);
	//	usleep(100000);
		direction(pin, "out");
		//usleep(50000);
	}
}

// unexports all used GPIO pins
void stop_gpio(const char **gpio)
{
	char pin[3];
	int i;
	for (i = 0; i < 8; i++) {
		strcpy(pin, gpio[i]);
		//printf("Unexporting GPIO %s\n", pin);
		unexport(pin);
		usleep(10000);
	}

}

// set leds based on user input
void set_leds(const char **gpio, int input)
{
	int i;
	unsigned int mask = 1;
	char bitvalue[2];
	for (i = 0; i < 8; i++) {
		// mask the input, store into makeresult string
		snprintf(bitvalue, 2, "%d", mask & input);
		// send value of bit to GPIO
		value(gpio[i], bitvalue);
		// right shift mask to get next bit
		mask = mask << 1;
	//	usleep(10000);
	}
}
