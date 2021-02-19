/* Osiris Thomas
 * main.c
 * 
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
	
	// checks for correct input
	if (argc != 2) {
		printf("Must enter one argument\n");
		exit(1);
	} 

	int input = atoi(argv[1]);
	printf("Entered input: %d\n", input);
	if (input < 0 || input > 0xFF) {
		printf("Input must be between 0x0 and 0xFF\n");
		exit(2);
	}
	
	const char *gpio[8] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	init_gpio(gpio);
	printf("Succesfully initialized GPIO\n");	
	
	set_leds(gpio, input);	
	
	stop_gpio(gpio);
	return 0; 
}

void init_gpio(const char **gpio)
{
	char pin[3];
	int i;
	for (i = 0; i < 8; i++) {
		strcpy(pin, gpio[i]);
		printf("Initializing GPIO %s\n", pin);
		exportpin(pin);
		usleep(10000);
		direction(pin, "out");
		usleep(10000);
	}
}

void stop_gpio(const char **gpio)
{
	char pin[3];
	int i;
	for (i = 0; i < 8; i++) {
		strcpy(pin, gpio[i]);
		printf("Unexporting GPIO %s\n", pin);
		unexport(pin);
		usleep(10000);
	}

}

void set_leds(const char **gpio, int input)
{
	int i;
	int mask = 1;
	char maskresult[2];
	for (i = 0; i < 8; i++) {
		// mask the input, store into makeresult string
		snprintf(maskresult, 2, "%d", mask & input);
		// send value of bit to GPIO
		value(gpio[i], maskresult);
		// right shift mask to get next bit
		mask = mask << 1;
	//	usleep(10000);
	}
}
