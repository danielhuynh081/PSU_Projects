#include <stdio.h>

//gcc -Wall -g -o f2c f2c.c
//./f2c
// January 12 2023
// Daniel Huynh, Jesse Chaney CS201, In-Class 1
// This program takes fahrenheit numbers and converts values to celsius


int main(void)
{
	float fahrenheit= 0.0f;
	float celsius =0.0;

	printf("Enter temperature in Fahrenheit:");
	if (scanf("%f", &fahrenheit) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

	celsius = (fahrenheit-32.0f) * 5.0f/9.0f;
	printf("\nCelcius: %.4f\n", celsius);

	return 0;
}
