#include <stdio.h>

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct House {
    char address[100];
    float price;
    int rooms;
    float area;
};
// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
int WorthBuying(struct House* h) {
    int wb = 0;
    float normal_price = (h->area) * 400;
    if ((h->price) < normal_price) {
        wb = 1;
        //printf("This house is worth buying!\n");
    }
    return wb;
}

// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int HousesWorthBuying(struct House* p, int len) {
       int cntr = 0;
        for (int i = 0; i < len; i++){
            if (WorthBuying(&p[i])){
                cntr++;
            }
        }
    printf("%d houses are worth buying.\n", cntr);
    return cntr;
}


int main() {
    struct House g;
    g.area = 200;
    g.price=90000;
    struct House z[] = {
        {"h", 2, 300, 600},
        {"i", 2, 500, 600},
        {"i", 22000, 5, 60}
    };

    WorthBuying(&g);
    HousesWorthBuying(z, 3);

    return 0;
}
