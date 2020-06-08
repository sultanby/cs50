#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int shift(char c)
{ 
    c  = toupper(c);
    return c = c - 'A';
}

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
        else 
        {
            string p = get_string("plaintext: ");
            printf("ciphertext: ");
            int j = 0;
            //int k = 0;
            for (int k = 0; k < strlen(p); k++, j++)
            {            
                int code_iter = j - (div(j, strlen(argv[1])).quot) * strlen(argv[1]);
                int key = shift(argv[1][code_iter]);
                if (isupper(p[k]))
                {
                    printf("%c", 'A' + (p[k] - 'A' + key) % 26);
                }
                else if (islower(p[k]))
                {
                    printf("%c", 'a' + (p[k] - 'a' + key) % 26);
                }
                else
                {
                    printf("%c", p[k]);
                    //k++;
                    j--;
                }
                //printf(" %c ", p[k]);
                //printf("%d ", code_iter);
                //printf("%d\n", key);
                //k++;
            }
            printf("\n");
            return 0;
        }
    }
}
