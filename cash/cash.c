#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_right(void)
{
    float n;
    do
    {
        n = get_float("Owed:");
    }
    while (n <= 0);
    return n;
}

int main(void)
{
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    float j = get_right();
    int cents = round(j * 100);
    int quarters = round(cents / 25);
    int remain1 = cents - quarters * 25;
    if (remain1 > 0) 
    {
        dimes = round(remain1 / 10);
        int remain2 = remain1 - dimes * 10;
        if (remain2 > 0)
        {
            nickels = round(remain2 / 5);
            int remain3 = remain2 - nickels * 5;
            if (remain3 > 0)
            {
                pennies = remain3;
            }
        }
    }
    
    printf("%d\n", quarters + dimes + nickels + pennies);   
}
