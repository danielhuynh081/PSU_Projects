#include <stdio.h>

//gcc -Wall -g -o ip ip.c
// ./ip
// January 17 2023
// Daniel Huynh, Jesse Chaney CS201, In-Class 2
// This program goes over inputting and outputting certain types

#define STRLEN 100

int main(void)
{
	// init variables
	char str1[STRLEN] = {'\0'};
	char str2[STRLEN] = {'\0'};
	char str3[STRLEN] = {'\0'};
	int matched =0;
	float f = 0;
	int matched =0;
    int i =0;
    unsigned u =0;
	char cleanup[STRLEN] = {'\0'};

//Read one string
	printf("--strings\n");
	fgets(str1, STRLEN, stdin);
	printf(">>%s<<\n", str1);

	scanf("%s", str2);
	printf(">>%s<<\n", str2);

	scanf("%s %s", str2, str3);
	printf(">>%s %s<<\n", str2, str3);

	printf("-- 3 strings\n");
	matched = scanf("%s %s %s", str1, str2, str3);
	printf(">>%s %s %s<< %d\n", str1, str2, str3, matched);



	printf("--intergers\n");
	scanf("%i", &i);
	printf("%i\n", i);

	printf("--hex\n");
	scanf("%x", &u);
	printf("%u\n", u);

	scanf("%x", &u);
	printf("%x\n", u);

	printf("--bogus hex\n");
	matched = scanf("%x", &u);
	printf("%x  %d\n", u, matched);

	fgets(cleanup, STRLEN, stdin);



	printf("--float\n");
	scanf("%f", &f);
	printf("%.2f\n", f);

	return 0;
}
