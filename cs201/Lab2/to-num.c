#include <stdio.h>
#include <string.h>

#define STRLEN 200
// Daniel Huynh, Jesse Chaney CS201, Jan 21 2023
// This program displays the ASCII values of a string in multiple number formats.
int main(void)
{

	char str1[STRLEN] = {'\0'};

	fgets(str1, STRLEN, stdin);

	printf("character output\n");
	for(int i = 0; i < strlen(str1)-1; ++i)
	{
		printf("%c ", str1[i] );
	}
	printf("\noctal output\n");
	for(int i = 0; i < strlen(str1)-1; ++i)
	{
		printf("0%o ", str1[i] );
	}
	printf("\ndecimal output\n");
	for(int i = 0; i < strlen(str1)-1; ++i)
	{
		printf("%d ", str1[i] );
	}
	printf("\nhex output\n");	
	for(int i = 0; i < strlen(str1)-1; ++i)
	{
		printf("0x%x ", str1[i] );
	}
	printf("\n");

	




	return 0;
}
