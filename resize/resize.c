// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("%d\n", argc);
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //argv[0] - shadow parameter, atoi change char to int
    int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    //printf("Strating image upscaler, upscale is: %d\n", n);
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int inputWidth = bi.biWidth;
    int inputHeight = bi.biHeight;
    bi.biWidth *= n;
    // determine padding for scanlines
    int padding = (4 - (inputWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingNew = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biHeight *= n;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingNew) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //initiating array
    RGBTRIPLE imgRow[bi.biWidth];
    //printf("New img height is: %d, new img width is: %d\n", bi.biHeight, bi.biWidth);
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inputHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < inputWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            //printf("Getting pixel at position: h: %d, w: %d. Color: r: %d, g: %d, b: %d\n", i, j, triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
            for (int l = 0; l < n; l++)
            {
                // write RGB triple to outfile
                imgRow[j * n + l] = triple;
                //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        // skip over padding, if any
        //printf("Input picture have width %d, so this picture have %d padding\n", inputWidth, padding);
        fseek(inptr, padding, SEEK_CUR);
        //printf("Ouptut picture have width %d, so this picture have %d padding\n", bi.biWidth, paddingNew);
        // then add it back (to demonstrate how)
        for (int m = 0; m < n; m++)
        {
            //printf("Array for new image row created.\n It contains: ");
            //for(int newRowIdx = 0; newRowIdx < bi.biWidth; newRowIdx++)
            //{
            //    printf("pos %d, r: %d, g: %d, b: %d; ", newRowIdx, imgRow[newRowIdx].rgbtRed, imgRow[newRowIdx].rgbtGreen, imgRow[newRowIdx].rgbtBlue);
            //}
            //printf("btw size of imgRow is: %lu\n", sizeof(imgRow));
            fwrite(&imgRow, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingNew; k++)
            {
                fputc(0x00, outptr);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
