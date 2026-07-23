#include <stdio.h>
#include <string.h>

int main()
{
	char * plines[3];
	char * ap= "abc";
	char * bp = "bcd";
	char cp[]= "cde";

	plines[0]=ap;
	plines[1]=bp;
	plines[2]= cp;

	printf("%s", *plines);
	printf("%c", *plines[0]);

	printf("%s", plines[0][0]);
}
