//This is a c-program that cyphers input text with the caesar cypher

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check for correct nb of cmdline vars
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }//check that the cmdlnvar is not letters
    if (islower(argv[1][1]) || isupper(argv[1][1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //convert argv[1] to an int named cph for cipher, so it is usable for "rotating" text
    int cph = atoi(argv[1]); //make the int base for the rotating
    int cph2 = cph % 26; // use the modulo so it doesnt rotate it too far
    int nb = 26; //variable for correcting roatations so lower and upper case stays lower and upper

    if (cph <= 0)//final check that the inputvar is valid
    {
        printf("Usage: ./caesar key\n");
        return 2;
    }

    else//parse each char for value, rotate by input if smaller or upper case
    {
        string pln = get_string("Plaintext: ");
        int len = strlen(pln);

        printf("ciphertext: ");//prints the word ciphertext

        for (int i = 0; i < len; i++)
        {
            pln[i] = abs(pln[i]);

            if (islower(pln[i]))
            {
                if ((abs(pln[i]) + cph2) >= 122)//make sure the char doesnt shoot too high
                {
                    pln[i] -= nb;
                }
                pln[i] += cph2;//add roation after nescassery correction is done.

            }

            else if (isupper(pln[i]))//added rotation for uppercase after lower case since they are a lower number omn the ascii table
            {
                pln[i] += cph2;
                if (pln[i] > 'Z')
                {
                    pln[i] -= nb;
                }
            }

            printf("%c", abs(pln[i]));//print each char after roatating.
        }

        printf("\n");//Adds bew line after all chars are printed.
    }
}