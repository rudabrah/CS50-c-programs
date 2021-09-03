//This is a C-program that resizes a given BMP-file image 

// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
        {
            fprintf(stderr, "Usage: copy infile outfile\n");
            return 1;
        }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // turn the input factor into variable n
    int n = atoi(argv[1]);

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer less than  or equal to 100\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

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
        return 5;
    }

    //print info for oversikt
    printf("before: %i %i %i %i\n", bi.biWidth, bi.biHeight, bi.biSizeImage, bf.bfSize);

    //gammel biwidth
    int biWidthO = abs(bi.biWidth);
    int biHeightO = abs(bi.biHeight);

    //skriv inn width og height n ganger
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine old padding for scanlines
    int paddingO = (4 - (biWidthO * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    //strl på bisizeimage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth+padding) * abs(bi.biHeight));

    //strl på bfsize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //print info for oversikt
    printf("After: %i %i %i %i\n", bi.biWidth, bi.biHeight, bi.biSizeImage, bf.bfSize);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0; i < biHeightO; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < n; j++)
        {
            fseek(inptr, bf.bfOffBits + i * (paddingO+biWidthO * sizeof(RGBTRIPLE)), SEEK_SET);

            for (int fiks = 0; fiks < biWidthO; fiks++)
            {

                 // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int p = 0; p < n; p++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                }

            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // add padding
            for (int pad = 0; pad < padding; pad++)
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