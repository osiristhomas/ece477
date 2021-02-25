/* Osiris Thomas
 * main.c
 * ECE 477 Lab 3 Part B
 * Displays the cpu temp on 8 LEDs
 * Each led lit up represents additional 10 degrees C
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
// display leds based on cpu temperature
void conv_value(const char **, float);

int main(int argc, char *argv[])
{
	float cpu_temp = 0.0;
	const char *gpio[8] = {"18", "23", "24", "25", "12", "16", "20", "21"};
	int file;	
	init_gpio(gpio);
	// enter loop until q is pressed
	while (1) {
		// access file where temperature is stored, read only
		file = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
		if (file == -1) {
			printf("Cannot open /proc/loadavg\n");
			exit(1);
		}
		cpu_temp = get_cpu(file);
		// divide by 1000 to make temperature more readable
		cpu_temp /= 1000;
		// print only up to 2 decimal places
		printf("CPU temp: %.2f C\n", cpu_temp);
		conv_value(gpio, cpu_temp);
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

// set leds based on input
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
	float temp;
	do {
		ch = '0';
		read(f, &ch, 1);
		buf[pos++] = ch;
	} while (ch != '\n');
	*(buf + pos) = '\0';
//	printf("%s\n", buf);
	temp = strtod(buf, &str);
	free(buf);
	return temp;
}

void conv_value(const char **gpio, float temp)
{
	if (temp > 60)
		set_leds(gpio, 255);
	else if (temp <= 55 && temp > 50)
		set_leds(gpio, 127);
	else if (temp <= 50 && temp > 45)
		set_leds(gpio, 63);
	else if (temp <= 45 && temp > 40)
		set_leds(gpio, 31);
	else if (temp <= 40 && temp > 35)
		set_leds(gpio, 15);
	else if (temp <= 35 && temp > 30)
		set_leds(gpio, 7);
	else if (temp <= 30 && temp > 25)
		set_leds(gpio, 3);
	else if (temp <= 25 && temp > 20)
		set_leds(gpio, 1);
	else set_leds(gpio, 0);
}
