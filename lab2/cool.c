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
		case 'A': 
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'b':
		case 'B':
			dash(1);
			dot(3);
			usleep(DAH);
			break;
		case 'c':
		case 'C': 
			dash(1);
			dot(1);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'd':
		case 'D': 
			dash(1);
			dot(2);
			usleep(DAH);
			break;
		case 'e':
		case 'E':
			dot(1);
			usleep(DAH);
			break;
		case 'f':
		case 'F':
			dot(2);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'g':
		case 'G':
			dash(2);
			dot(1);
			usleep(DAH);
			break;
		case 'h':
		case 'H':
			dot(4);
			usleep(DAH);
			break;
		case 'i':
			dot(2);
			usleep(DAH);
			break;
		case 'j':
		case 'J':
			dot(1);
			dash(3);
			usleep(DAH);
			break;
		case 'k':
		case 'K':
			dash(1);
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'l':
		case 'L':
			dot(1);
			dash(1);
			dot(2);
			usleep(DAH);
			break;
		case 'm':
		case 'M':
			dash(2);
			usleep(DAH);
			break;
		case 'n':
		case 'N':
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 'o':
		case 'O':
			dash(3);
			usleep(DAH);
			break;
		case 'p':
		case 'P':
			dot(1);
			dash(2);
			dot(1);
			usleep(DAH);
			break;
		case 'q':
		case 'Q':
			dash(2);
			dot(1);
			dash(1);
			usleep(DAH);
			break;
		case 'r':
		case 'R':
			dot(1);
			dash(1);
			dot(1);
			usleep(DAH);
			break;
		case 's':
		case 'S':
			dot(3);
			usleep(DAH);
			break;
		case 't':
		case 'T':
			dash(1);
			usleep(DAH);
			break;
		case 'u':
		case 'U':
			dot(2);
			dash(1);
			usleep(DAH);
			break;
		case 'v':
		case 'V':
			dot(3);
			dash(1);
			usleep(DAH);
			break;
		case 'w':
		case 'W':
			dot(1);
			dash(2);
			usleep(DAH);
			break;
		case 'x':
		case 'X':
			dash(1);
			dot(2);
			dash(1);
			usleep(DAH);
			break;
		case 'y':
		case 'Y': 
			dash(1);
			dot(1);
			dash(2);
			usleep(DAH);
			break;
		case 'z':
		case 'Z':
			dash(2);
			dot(2);
			usleep(DAH);
			break;
		default: break;
		}
		str++;
	}
}
