/* Osiris Thomas
 * cool.c
 * 
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "led.h"
#define DIH 200000
#define DAH 600000
#define SPACE 1400000
//#include "cool.h"

// initializes all useable GPIO pins
void init_gpio(const char **);
// unexports all used GPIO pins
void stop_gpio(const char **);
// set leds based on user input
void set_leds(const char **, int);
void dot(int);
void dash(int);
void morse(char *);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Must input one string\n");
		exit(1);
	}
	
	const char *gpio[8] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	init_gpio(gpio);
	//printf("Succesfully initialized GPIO\n");	
	
	morse(argv[1]);
	
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
		usleep(20000);
		direction(pin, "out");
		usleep(20000);
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

void dot(int num)
{
	int i;
	for (i = 0; i < num; i++) {
		value("18", "1");
		usleep(DIH);
		value("18", "0");
		usleep(DIH);
	}
}

void dash(int num)
{
	int i;
	for (i = 0; i < num; i++) {
		value("18", "1");
		usleep(DAH);
		value("18", "0");
		usleep(DIH);
	}
}

void morse(char *str)
{
	while (*str != '\0') {
		switch (*str) {
		case ' ': 
			usleep(SPACE);
			break;
		case 'a': 
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'b':
			dash(1);
			dot(3);
			usleep(DAH);
			break;
		case 'c': 
			dash(1);
			dot(1);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'd': 
			dash(1);
			dot(2);
			usleep(DAH);
			break;
		case 'e':
			dot(1);
			usleep(DAH);
			break;
		case 'f':
			dot(2);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'g':
			dash(2);
			dot(1);
			usleep(DAH);
			break;
		case 'h':
			dot(4);
			usleep(DAH);
			break;
		case 'i':
			dot(2);
			usleep(DAH);
			break;
		case 'j':
			dot(1);
			dash(3);
			usleep(DAH);
			break;
		case 'k':
			dash(1);
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'l':
			dot(1);
			dash(1);
			dot(2);
			usleep(DAH);
			break;
		case 'm':
			dash(2);
			usleep(DAH);
			break;
		case 'n':
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'o':
			dash(3);
			usleep(DAH);
			break;
		case 'p':
			dot(1);
			dash(2);
			dot(1);
			usleep(DAH);
			break;
		case 'q':
			dash(2);
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'r':
			dot(1);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 's':
			dot(3);
			usleep(DAH);
			break;
		case 't':
			dash(1);
			usleep(DAH);
			break;
		case 'u':
			dot(2);
			dash(1);
			usleep(DAH);
			break;
		case 'v':
			dot(3);
			dash(1);
			usleep(DAH);
			break;
		case 'w':
			dot(1);
			dash(2);
			usleep(DAH);
			break;
		case 'x':
			dash(1);
			dot(2);
			dash(1);
			usleep(DAH);
			break;
		case 'y': 
			dash(1);
			dot(1);
			dash(2);
			usleep(DAH);
			break;
		case 'z':
			dash(2);
			dot(2);
			usleep(DAH);
			break;
		default: break;
		}
		str++;
	}
}
