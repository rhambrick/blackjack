/*
Rules: 1) User starts with $100 in they account
2) User places bet, or presses 'q' to quit
3) bet must be > 0 and an int bc we only have poker chips
4) Cards are dealt as numbers.
5) User can hit, stand, double bet, or split if both their cards are =
6) Dealer stands on 17 or higher after user stands or busts
7) 2:1 pay
8) just reset game if negative, i ain't a real casino

Side note: there's a warning about passing in my string into the isInt function.
char string[10] is passed into the function isInt as a pointer, char* string.
So isInt is getting the first element of our string (and it's max size defined is [10])
I am not sure why the warning is there, something to do with the pointer but it compiles so... whatever?
Definetly a rushed project.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIMIT 10

bool isInt(char* string)
{
    int length = strlen(string);
   
    if (length == 0)
    {
        return false;
    }
   
    if (string[0] == '-' || string[0] == '0')
    {
        return false;
    }
   
    if (string[0] == '0' && length > 1)
    {
        return false;
    }
   
    for (int i = 0; i< length; i++)
    {
        if (string[i] < 48 || string[i] > 57) // ascii 0-9 is 48-57
        {
            return false;
        }
    }
    return true;    
}

int main()
{
    printf("--BlackJack--\n\nDealer stands on 17 or higher.\n\nBets must be integer > 0.\n\nControls: h = hit, s = stand, d = double bet. ");

    int bank = 100; // pull from file later
      
    // rng setup
    srand(time(NULL));

    char bet[10];   // 10 digits is max bc i said so
    int dealerCards = 0;
    int playerCards = 0;
    char command = '0';

    bool running = true;
    bool playerBust = false;
    bool dealerBust = false;

    while(running)
    {
        printf("You have %i chips.\n\nEnter your bet (q to quit): ", bank);
    
        fgets(bet, MAX_LIMIT, stdin);   // safe way to only read MAXLIMIT chars
        bet[strcspn(bet, "\n")] = 0; // <-- Necessary step from textbook to flush \n with fgets

        if (bet[0] == 'q')
        {
            running = false;
            break;
        }

        if (isInt(&bet))    // if bet is an integer we proceed and deal player first
        {
            int bet_integer = atoi(bet);    // casting bet as integer, and it's okay here since we parsed it as valid

            if (bet_integer > bank)
            {
                printf("\n  If you're broke just say that.\n  (Restart the game if you're in debt).\n\n");
                continue;
            }

            playerCards = (rand() % 21) + 1;  // randomly generate player cards total 1 thru 21
            dealerCards = (rand() % 10) + 1;  // randomly generate dealer's upcard

            if (playerCards == 21)
            {
                printf("!!!Blackjack!!!\n");
                continue;
            }

            printf("\n  Dealer's upcard is %i.\n  You have %i.\n\nHit or stand: ", dealerCards, playerCards);
            command = getchar();
            while (getchar() != '\n' && getchar() != EOF);  // flush newline from buffer
            
            // PLAYER'S TURN LOOP
            while (playerCards <= 21 && playerBust == false) 
            {
                if (command == 'h')
                {
                    playerCards = playerCards + (rand() % 10) + 1;
                    if (playerCards > 21)
                    {
                        printf("Bust!\n");
                        playerBust = true;
                        break;
                    }
                    if (playerCards == 21)
                    {
                        printf("\n!!!Blackjack!!!\n");
                    }
                }
                if (command == 's')
                {
                    break;
                }
                printf("You have %i.\n\nHit or stand: ", playerCards);
                command = getchar();
                while (getchar() != '\n' && getchar() != EOF);  // flush newline from buffer
            }

            // DEALER'S TURN LOOP
            while (dealerCards < 17)
            {
                dealerCards = dealerCards + (rand() % 10) + 1;
            }
            printf("\n  Dealer ends on %i.\n", dealerCards);
            if (dealerCards > 21)
            {
                dealerBust = true;
            }

            // WINNER CHECK
            if (dealerBust && !playerBust)
            {
                printf("\nYou won %i chips!\n\n", bet_integer);
                bank = bank + bet_integer;
                continue;

            }
            if (playerBust)
            {
                bank = bank - bet_integer;
                continue;
            }
            if (dealerCards > playerCards)
            {
                bank = bank - bet_integer;
                continue;
            }
            if (playerCards > dealerCards)
            {
                printf("\nYou won %i chips!\n\n", bet_integer*2);
                bank = bank + bet_integer;
                continue;
            }
        }

        else
        {
            printf("\nbro, you can't bet %s chips.\n\n", bet);
            continue;
        }

    }

    return 0;
}

// Ok, I like it. But who is going to want to compile some C?? No one. So let's migrate to a JS app where we can have a GUI and run the program in any browser.