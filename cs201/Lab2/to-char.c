#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// Daniel Huynh, Jesse Chaney CS201, Jan 21 2023
// This program converts decimal, octal, or hexadecimal ASCII input into text.

int main(void)
{
    int num2[200];
    int num3 = 10;
    int size = 0;
    int print = 0;
    int num = 0;

    while (true)
    {
        scanf("%d", &num);

        if (num == 10)
        {
            printf("decimal input\n");

            while (num3 != 0)
            {
                scanf("%d", &num3);
                num2[size] = num3;
                ++size;
            }

            int array[size];

            for (int i = 0; i < size; ++i)
            {
                array[i] = num2[i];
            }

            while (print < size)
            {
                if (array[print] != '\0')
                {
                    printf("%c", array[print]);
                }
                ++print;
            }

            printf("\n");
        }

        if (num == 8)
        {
            printf("octal input\n");

            while (num3 != 0)
            {
                scanf("%o", &num3);
                num2[size] = num3;
                ++size;
            }

            int array[size];

            for (int i = 0; i < size; ++i)
            {
                array[i] = num2[i];
            }

            while (print < size)
            {
                if (array[print] != '\0')
                {
                    printf("%c", array[print]);
                }
                ++print;
            }

            printf("\n");
        }

        if (num == 16)
        {
            printf("hex input\n");

            while (num3 != 0)
            {
                scanf("%x", &num3);
                num2[size] = num3;
                ++size;
            }

            int array[size];

            for (int i = 0; i < size; ++i)
            {
                array[i] = num2[i];
            }

            while (print < size)
            {
                if (array[print] != '\0')
                {
                    printf("%c", array[print]);
                }
                ++print;
            }

            printf("\n");
        }
    }

    return 0;
}