#include <stdio.h>
#define MARKETPRICE 400
// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct house {
    char address[50];
    float price;
    int rooms;
    float area;
};

// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
int worth_buying(struct house *m);
// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int houses_to_buy(struct house *n, int len);

int main()
{
    struct house my_house = {"csovar", 230000000, 3, 4.1};
    struct house array[] = {
        {"csovar", 230, 3, 4.1},
        {"csovar", 100000000000000000000000, 3, 4.1},
        {"csovar", 200, 3, 4.1}
    };
    printf("%d\n", worth_buying(&my_house));
    printf("%d\n", houses_to_buy(array, 3));
    return 0;
}

int worth_buying(struct house *m)
{
    int buy = 0;
    float m_price = (m->area)* MARKETPRICE;
    if (m_price > (m->price)) {
        buy = 1;
        //printf("This house is worth buying.\n");
    } else {
        //printf("This house is not worth buying.\n");
    }
    return buy;
}

int houses_to_buy(struct house *n, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++) {
        int buy = worth_buying(&(n[i]));
        if (buy == 1) {
            count++;
        }
    }
    return count;
}
