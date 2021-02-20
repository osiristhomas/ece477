/* Osiris Thomas
 * led.c
 * Functions for handling GPIO
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "led.h"
// exports pin passed
void exportpin(const char *pin)
{
	int file = open("/sys/class/gpio/export", O_WRONLY);
	if (file == -1) 
		printf("Error in export, open\n");
	// export pin
	if (write(file, pin, 2) > 2)
		printf("Error in export, write\n");
	close(file);
}

// unexports pin passed
void unexport(const char *pin)
{
	int file = open("/sys/class/gpio/unexport", O_WRONLY);
	// unexport pin
	write(file, pin, 2);
	close(file);
}

// writes passed value to passed pin
void value(const char *pin, char *value)
{
	char *path = malloc(FILENAME_MAX);
	// create string of pin file
	strcpy(path, "/sys/class/gpio/gpio");
	strncat(path, pin, 2);
	strncat(path, "/value", 10);
	int file = open(path, O_WRONLY);
	if (file == -1)
		printf("Cannot open %s\n", path);
	//printf("Writing %d to %s\n", value > 0 ? 1 : 0, path);
	write(file, value, 2);
	close(file);
	free(path);
}

// sets the direction
void direction(const char *pin, char *dir)
{
	char *path = malloc(FILENAME_MAX);
        // create string of pin file
        strcpy(path, "/sys/class/gpio/gpio");
        strcat(path, pin);
        strcat(path, "/direction");
        int file = open(path, O_WRONLY);
        // write the value passed into the file
        write(file, dir, sizeof(char) * 5);
	//printf("Wrote \"out\" to %s\n", path);
        close(file);
        free(path);
}
