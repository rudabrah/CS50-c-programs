//This is a C-program that divides a given amount of cash in to the minimum devisable amount of coins

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //making ints for each type of change
    int qu = 25;
    int di = 10;
    int ni = 5;
    int pe = 1;
    float owed;
    //get valid user input, make it usable with the coins
    do
    {
    owed = get_float("Owed: ");
    }
    while(owed < 0.001);
    
    int coins = round(owed * 100);
    //ints for use in the loop
    int cu = 0;
    int cr = coins;
    //loop through each coin, if they fit, add 1 to the print
    for (cr = coins; cr > 0; cr--)
    {
        while (cr >= qu)
        {
            cu++;
            cr = cr - qu;
        }
        
        while (cr >= di && qu > cr)
        {
            cu++;
            cr = cr - di;
        }
       
        while (cr >= ni && di > cr)
        {
            cu++;
            cr = cr - ni;
        }
        
        while (cr >= pe && ni > cr)
        {
            cu++;
            cr--;
        }
        

    }
    printf("%i", cu);
}

