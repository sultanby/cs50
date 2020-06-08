#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        //printf("Success\n%i\n", k);
        //return 0;
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int j = 0; j < strlen(p); j++)
        {
            if (isupper(p[j]))
            {
                printf("%c", 'A' + (p[j] - 'A' + k) % 26);
            }
            else if (islower(p[j]))
            {
                printf("%c", 'a' + (p[j] - 'a' + k) % 26);
            }
            else
            {
                printf("%c", p[j]);
            }
        }
        printf("\n");
        return 0;
    }
}
