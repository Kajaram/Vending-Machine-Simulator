/*
- 2024-06-10
- pop.c
- Kajaram Kanthasamy
- Student ID: 501115080
- Assignment #3 - simulate vending machine
- CCPS393 Section BA0
- Instructor: L. Hiraki
- Purpose: To raise awareness that software development is often a commercial (paid) competitive activity, and the importance of designing for reducing software maintenance costs.

- I certify that the program and code are my own work

*/


#include <stdio.h>
#include <stdlib.h>

// Define coin values as constants for Single Point of Truth
#define NICKEL_VALUE 5
#define DIME_VALUE 10
#define PENTE_VALUE 20
#define MIN_PRICE 30
#define MAX_PRICE 115
#define PRICE_INCREMENT 5

// Constants for the accepted coin denominations
#define COIN1 NICKEL_VALUE
#define COIN2 DIME_VALUE
#define COIN3 PENTE_VALUE

// Function to calculate and display the change given
void dispenseChange(int change) {
    int dimes = change / DIME_VALUE; // Change computation uses constant names
    int nickels = (change % DIME_VALUE) / NICKEL_VALUE;
    printf("    Change given: %d centimes as %d dime(s) and %d nickel(s).\n", change, dimes, nickels);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please specify the selling price as a command line argument.\n");
        printf("Usage: %s [price]\n", argv[0]);
        return 1;
    }

    int price = atoi(argv[1]);
    if (price < MIN_PRICE || price > MAX_PRICE) {
        printf("Price must be from %d to %d centimes inclusive.\n", MIN_PRICE, MAX_PRICE);
        return 1;
    }

    if (price % PRICE_INCREMENT != 0) {
        printf("Price must be a multiple of %d.\n", PRICE_INCREMENT);
        return 1;
    }

    printf("Welcome to my C Pop Machine!\n");
    printf("Pop is %d centimes. Please insert any combination of nickels [N or n], dimes [D or d], or Pentes [P or p]. You can also press R or r for coin return.\n", price);

    int totalInserted = 0;
    char input;

    while (1) {
        printf("Enter coin (NDPR): ");
        scanf(" %c", &input);

        switch (input) {
            case 'N': case 'n':
                totalInserted += COIN1;
                printf("  Nickel detected.\n");
                break;
            case 'D': case 'd':
                totalInserted += COIN2;
                printf("  Dime detected.\n");
                break;
            case 'P': case 'p':
                totalInserted += COIN3;
                printf("  Pente detected.\n");
                break;
            case 'R': case 'r':
                dispenseChange(totalInserted);
                totalInserted = 0;
                printf("Pop is %d centimes. Please insert any combination of nickels [N or n], dimes [D or d], or Pentes [P or p]. You can also press R or r for coin return.\n", price);
                continue;  // Ready for the next transaction
            case 'K': case 'k':
                dispenseChange(totalInserted);
                printf("  Shutting down. Goodbye.\n");
                return 0;
            default:
                printf("  Unknown coin rejected.\n");
                break;
        }

        if (totalInserted > 0) {
            printf("    You have inserted a total of %d centimes.\n", totalInserted);
            if (totalInserted < price) {
                printf("    Please insert %d more centimes.\n", price - totalInserted);
            }
        }

        if (totalInserted >= price) {
            printf("    Pop is dispensed. Thank you for your business! Please come again.\n");
            if (totalInserted > price) {
                dispenseChange(totalInserted - price);
            }
            totalInserted = 0;  // Reset for the next customer
            printf("Pop is %d centimes. Please insert any combination of nickels [N or n], dimes [D or d], or Pentes [P or p]. You can also press R or r for coin return.\n", price);
        }
    }
}


