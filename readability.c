//This is a C-program to decide the "readability" of a given tekst based on the count of words, letters and symbols - this was part of CS50 course

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //declare all variables
    float S, L;
    float ltr = 0; //letters
    float wrd = 1; //words, added one since i count it with the spaces
    float pkt = 0; //sentence enders . ! ?
    int index = 0;

    string txt = get_string("tekst:");

    int i, n; //declare variables for loop
    //Looping through all the chars in the input to look for specifics, then adding in the floats decared earlier
    for (i = 0, n = strlen(txt); i < n; i++)
    {
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            pkt++;
        }
        else if (txt[i] >= 'A' && txt[i] <= 'z')
        {
            ltr++;
        }
        else if (txt[i] == ' ')
        {
            wrd++;
        }
    }
    //in order to average things out, devided words by 100, then used that variable for the parts of the index variable
    float phwrd = wrd / 100;
    L = ltr / phwrd;
    S = pkt / phwrd;

    index = round((0.0588 * L) - (0.296 * S) - 15.8);
    //just added som ifs to give expected answers.
    if (index >= 1 && index <= 16)
    {
        printf("Grade %d\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}