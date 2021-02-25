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
// set leds based on cpu load
void set_leds(const char **, int);
// reads the first value of a line in a file
float get_cpu(int);
// display leds based on how busy cpu is
void conv_value(const char **, float);

int main(int argc, char *argv[])
{
	//char input = '0';
	float cpu_load = 0.0;
	const char *gpio[8] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	int file;
		
	// open file with read only access
	init_gpio(gpio);
	printf("Reading /proc/loadavg. Press 'q' to quit.\n");
	// enter loop until q is pressed
	while (1) {
		file = open("/proc/loadavg", O_RDONLY);
		if (file == -1) {
			printf("Cannot open /proc/loadavg\n");
			exit(1);
		}
		cpu_load = get_cpu(file);
	//	printf("%f\n", cpu_load);
		conv_value(gpio, cpu_load);
		close(file);
		sleep(2);
	}	
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

// set leds based on cpu usage
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

float get_cpu(int f)
{
	char *buf = calloc(10, sizeof(char));
	int pos = 0;
	char *str;
	char ch = '0';
	float load;
	do {
		ch = '0';
		read(f, &ch, 1);
		buf[pos++] = ch;
	} while (ch != ' ');
	*(buf + pos) = '\0';
//	printf("%s\n", buf);
	load = strtod(buf, &str);
	free(buf);
	return load;
}

void conv_value(const char **gpio, float load)
{
	if (load > 4)
		set_leds(gpio, 255);
	else if (load <= 4 && load > 2)
		set_leds(gpio, 127);
	else if (load <= 2 && load > 1)
		set_leds(gpio, 63);
	else if (load <= 1 && load > 0.5)
		set_leds(gpio, 31);
	else if (load <= 0.5 && load > 0.25)
		set_leds(gpio, 15);
	else if (load <= 0.25 && load > 0.125)
		set_leds(gpio, 7);
	else if (load <= 0.125 && load > .0625)
		set_leds(gpio, 3);
	else if (load <= 0.625 && load > 0.03125)
		set_leds(gpio, 1);
	else set_leds(gpio, 0);
}
