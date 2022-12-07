/*************************************************************************
 *
 *  Author:           Emmanuel Lumanze Jr
 *  Label:            P03
 *  Title:            Blackjack Program
 *  Course:           CMPS 2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *        This is Blackjack the card game.
 *
 *  Files:
 *       main.cpp        : driver program
 *       colors.h        : header file with colors defintion
 *       blackjack.hpp   : implementations
 *
 *************************************************************************/

#include "blackjack.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

// Here is where I created a struct a designed its variables
struct Player {
  string name;
  int age;
  int bet;
  int money;
};

// drop menu at the beginning of the game
void MainMenu() {
  cout << "Please select an option below: " << endl;
  cout << "1) Brief Overview" << endl;
  cout << "2) Begin game!" << endl;
  cout << "Selection : ";
}

int cardVal(vector<Card *> cards, int cardAmount) {
  int t = 0; // total

  for (int i = 0; i < cardAmount; i++) {
    cardAmount == 2;

    if (cards[i]->getRank() >= 10) {
      // add 10 to the total if it's 10, J, Q, K
      t += 10;
    } else {
      t += cards[i]->getRank() + 1;
    }
  }
  return t;
}

// function that allows the player to go
void playerBet(Player &user) {
  int bet = 0;

  do {
    cout << "" << user.name
         << " how much money would you like to bet? (Must be greater than $5 "
            "and less than $"
         << user.money << ")" << endl;
    cout << "$";
    cin >> bet;
    cout << endl;

  } while (!(bet >= 5 && bet <= user.money));

  // updates user's money
  user.money -= bet;
  user.bet = bet;
}

// this function is for the game
void game(Player &user, Player &dealer) {

  // shows the player bet
  playerBet(user);
  system("clear");
  cout << "Player's money: $" << user.money << endl;
  cout << "Player's Bet: $" << user.bet << endl;

  // creates player and dealer's hand
  srand(time(0));
  int playerHand = 2;
  int dealerHand = 2;

  // holds player's hand & dealer's hand
  vector<Card *> playerCards;
  vector<Card *> dealerCards;

  // randomly picks card from the deck
  for (int i = 0; i < 2; i++) {
    playerCards.push_back(new Card(rand() % 52));
    dealerCards.push_back(new Card(rand() % 52));
  }

  cout << endl;
  cout << user.name << " card score: " << cardVal(playerCards, 2) << endl;

  cout << "Player's cards: " << endl << endl;
  printCardVector(playerCards, 2); // prints player's cards

  cout << "Dealer's visible card: " << endl << endl;
  printSingleCard(dealerCards); // prints dealer's visible card

  int playerCount = 0;
  string playerSelection = "H";

  while (playerSelection == "H" && !(user.money < 10)) {
    cout << endl << "Enter H to Hit or S to Stand" << endl;
    cout << "Selection: ";
    cin >> playerSelection;

    // here if the player wants to hit we give a new card and we erase the first
    // card and give a new card.
    if (playerSelection == "H" || playerSelection == "h") {
      cout << endl << "Player's new cards: " << endl;
      playerCards.erase(playerCards.begin());
      playerCards.push_back(new Card(rand() % 52));
      playerHand--;

      // here we print new cards and give a new count
      printCardVector(playerCards, playerHand);
    } else if (playerSelection == "S" || playerSelection == "s") {
      playerCount = cardVal(playerCards, 2);
    }
  }

  int playerTotalHand = cardVal(playerCards, playerHand);
  int dealerTotalHand = cardVal(dealerCards, dealerHand);

  // RESULTS

  // if the sum of the user's cards is equal to 21 then the user wins
  if (cardVal(playerCards, playerHand) == 21) {
    cout << endl;
    cout << "Winner Winner Chicken Dinner!" << endl;
    user.money += user.bet;

    cout << "Your new balance is: $ " << user.money << endl;
  }

  // if the sum of the user's cards is more than 21 then the user's busts
  else if (cardVal(playerCards, playerHand) > 21) {
    cout << endl;
    cout << "Aw man you've busted!" << endl;
    user.money -= user.bet;

    cout << "Check out your new balance : $ " << user.money << endl;
  }

  // if the sum of the user's hand is less than 21 then keep going
  else {
    cout << endl;
    // cout << "Here are your final cards " << user.name << " : " << endl;
    // printCardVector(playerCards, playerHand);
    cout << endl << "The dealer's seen cards: " << endl;
    printCardVector(dealerCards, dealerHand);

    // if (dealerTotalHand <= 16 && !(dealerTotalHand >= 21)) {
    //     dealerHand++;
    //     dealerCards.push_back(new Card(rand() % 52));
    //     cout << "Dealer's new hand" << endl;
    //     printCardVector(dealerCards, dealerHand);
    //     dealerTotalHand = cardVal(dealerCards, dealerHand);
    // }

    // if dealer's card sum is more than 21 then the user wins
    if (dealerTotalHand > 21) {
      cout << endl;
      cout << "Looks like dealer busted, you win! Winner Winner Chicken Dinner!"
           << endl;
      user.money += user.bet;

      cout << "Take a look at your new balance: $ " << user.money << endl;
    }

    // if the dealer has more than the user, dealer wins
    else if (dealerTotalHand > playerTotalHand) {
      cout << endl;
      cout << "How you let the dealer win!" << endl;
      cout << "LOSER" << endl;
      user.money -= user.bet;

      cout << "Here's your new balance: $ " << user.money << endl;
    }

    // if the dealer has the same sum as the player, it's tie
    else if (dealerTotalHand == playerTotalHand) {
      cout << endl;
      cout << "It comes to my attention that YOU and the Dealer came to a DRAW!"
           << endl;

      cout << "Check out your new balance: $ " << user.money << endl;
    }

    // if the player has more than the dealer, user win
    else if (playerTotalHand > dealerTotalHand) {
      cout << endl;
      cout << "Bring out the fryer, you have won! Winner Winner Chicken Dinner!"
           << endl;
      user.money += user.bet;

      cout << "Check out your new balance: $ " << user.money << endl;
    }
  }
}

int main() 
{
  srand(time(0));
  string name;
  int age;
  int money = 0;
  int bet = 0;

  // creating user and dealer
  Player user;
  Player dealer;

  // naming dealer
  dealer.name = "Dealer";

  // create variables
  int selection;          // drop down menu
  string continuePlaying; // player's option to keep playing or stop
  string addedMoney;      // if chooses to keep playing they have to add money

  // Clears screen to start a new game
  system("clear");

  // welcome message that prints at the start of the game
  cout
      << "I'm about to empty your pockets, My name Is Emmanuel Lumanze Jr, "
         "I will be your MC for the night, and this is my Blackjack! Lets Play!"
      << endl
      << endl;

  do {
    // this function displays menu and takes user input
    MainMenu();
    cin >> selection;

    // selection lets user see if they want to read instructions
    if (selection == 1) {
      system("clear"); // clears screen
      // gameRules();      // displays the rules
    } else if (selection == 2) // this is the selection to play the game
    {
      system("clear");

      cout << "Let the game begin!" << endl << endl;
      cout << "What is your name?" << endl; // gets the user's name
      cin >> user.name;
      cout << endl;

      // prints user's age
      cout << "How old are you?" << endl;
      cin >> user.age;
      cout << endl;

      // checks the age of user
      if (user.age < 18) {
        cout << "HAHA nice try you know you're too young to be playing this "
                "game. "
                "Come back in a when you reach 18 youngster!"
             << endl
             << endl;
      } else {
        do {
          cout
              << "How much money would you like to deposit? Don't be a chicken!"
              << endl; // deposit from the user
          cout << "$";
          cin >> user.money;

          cout << endl;
          game(user, dealer); // starts the game

          // checks amount of money user has
          if (user.money > 0) {
            cout << endl;
            cout << "Click on SPACEBAR to continue or E to exit the game: "
                 << endl;
            cout << "Selection: ";
            cin >> continuePlaying;
            cout << endl;
          }

          // if user has no money ask if they want to add money or quit
          else if (user.money <= 5) {
            cout << endl;
            cout << "You out of money, your pockets empty. Press A to add "
                    "money or E "
                    "to exit"
                 << endl;
            cout << "Selection: ";
            cin >> addedMoney;
            cout << endl;

            do {
              if (addedMoney == "A" || addedMoney == "a") {
                cout << "How much money do you wan to add? Oh my bad I forgot "
                        "your significant other was gone get you if you bet "
                        "too much!"
                     << endl; // add funds
                cout << "$ ";
                cin >> user.money;

                // restart game with added money
                game(user, dealer);
              } else if (addedMoney == "E" || addedMoney == "e") {
                cout << "Ah Ha see you again when your significant other gives "
                        "you your allowence!";
                cout << endl;
              }
            } while (addedMoney != "Y" || addedMoney != "y" ||
                     addedMoney != "N" || addedMoney != "n");
          }
        } while (continuePlaying == "Y" || continuePlaying == "y");
      }
    }
  }

while (selection != 2)
  ; // selections asks if they want to play again

cout << "Hope you had fun losing " << user.name << " you have $" << user.money
     << " in your account" << endl;
cout << "Do you dare come back?!" << endl;

return 0;
}
