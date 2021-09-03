//This is a C-program that "recovers" jpg files

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(void)
{
    // open memory card file
    FILE* input = fopen("card.raw", "r");
    if (input == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }

    // lag en buffer
    unsigned char buffer[BUFFER_SIZE];

    // filnavnteller
    int filteller = 0;

    FILE* bilde = NULL;

    // se om vi har funnet en jpg eller ikke
    int jpg_found = 0;

    // gå igjennom kortfilene og se at ikke det er noen blokker igjen
    while (fread(buffer, BUFFER_SIZE, 1, input) == 1)
    {
        // les de første 4 bytesa og se etter signatur
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpg_found == 1)
            {
                // Vi fant et nytt bilde, så lukk det som er åpent
                fclose(bilde);
            }
            else
            {
                // jpg er oppdaget, skriv nytt bilde
                jpg_found = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filteller);
            bilde = fopen(filename, "a");
            filteller++;
        }

        if (jpg_found == 1)
        {
            // write 512 bytes to file once we start finding jpgs
            fwrite(&buffer, BUFFER_SIZE, 1, bilde);
        }

    }

    // close files
    fclose(input);
    fclose(bilde);

    return 0;
}