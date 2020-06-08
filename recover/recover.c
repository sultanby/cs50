#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//defining a term BYTE for one-byte numbers
typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    //wrong usage alarm
    if (argc != 2)
    {
        printf("%d\n", argc);
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    //wrong input alarm
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //initiate an array-buffer size of 512 bytes
    BYTE buffer[512];
    //counter for images
    int imgCount = 0;
    //outfile is empty
    FILE *output = NULL;
    char filename[8];

    //read the file(data, size of each element, number of elements to read, inptr-file to read from)
    while (true)
    {
        //read into an input
        int bytesRead = fread(buffer, sizeof(BYTE), 512, input);

        //break the loop then we in the end of the card
        if (bytesRead == 0 && feof(input))
        {
            break;
        }

        //check for jpeg header and closing previous file and adding to image counting
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && output != NULL)
        {
            fclose(output);
            imgCount++;
        }

        //opening a file to writing in
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", imgCount);
            output = fopen(filename, "w");
        }

        //writing into an output
        if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, output);
        }
    }

    // close infile
    fclose(input);

    // close outfile
    fclose(output);

    // success
    return 0;
}
