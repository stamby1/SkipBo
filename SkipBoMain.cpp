//Sharmila Tamby, Amy He, Eric Walker, Tony Kim (Sang Yeon Kim) 
//stamby1, ahe3, ewalke31, skim340
//Final Project SkipBo
//Main file 
#include "Game.h" 
#include "Players.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <cstdio>

using std::cout; using std::cin; 
using std::endl; using std:: string; 

int main(void){
   Game *gptr = new Game();
   Game & g = *gptr; 
   int currentPlayer = 0;
   bool valid = false; 
   cout << "Welcome to Skip-Bo!" << endl; 
   cout <<  "Please enter your number choice to play:" <<endl;
   cout << "1. Start New Game" << endl; 
   cout << "2. Load Existing game" << endl ; 
   cout << "Choice: " ; 

   //asks user if they want to save or load the game
   int choice; 
   while (!valid){
     try{
       cin >> choice; 
       valid = true; //they must enter in an integer otherwise, invalid choice
       cout << endl;
     }catch (int e){
       cout << "Invalid answer. Please enter your number choice again:" <<endl; 
       cout << "1. Start New Game" << endl; 
       cout << "2. Load Existing game" << endl ; 
     }
   }
   int humans, stock, totalplayers =0;
   //create an exception if not choice != 1, 2
   if (choice==1){ //user would like to start new game 
     valid = false; 
     cout << "How many total players? (2-6 allowed): "; 
     while (!valid){
       try{
	 cin >> totalplayers; 
	 valid = true; 
	 cout << endl; 
       } catch (int e){ //will say invalid if user doesn't enter in an integer
	 cout << "Invalid answer. How many total players? (2-6 allowed): ";
         valid = false;
       }
     }
     while (totalplayers <2 || totalplayers >6){
       cout << "Invalid answer. How many total players? (2-6 allowed): ";
       cin >> totalplayers; 
       cout << endl; 
     }

     
     valid = false;
     cout  << "How many human players? (1-" << totalplayers << " players allowed): "; //the user can't have more human players than total players
     while (!valid){
       try{
	 cin >> humans; 
	 valid = true; 
	 cout << endl; 
       } catch (int e){ //will say invalid if user doesn't enter in an integer
	 cout << "Invalid answer. How many human players? (1-" << totalplayers << " players allowed): ";
         valid = false;
       }
     }

     while (humans>totalplayers || humans <1){ //the user can't have more human players than total players
       cout << "Invalid answer. How many human players? (1-" << totalplayers << " players allowed): ";
       cin >> humans; 
       cout << endl; 
     }

     string name; 
     for(int i=0; i < humans; i++){ //creating human players
       cout << "Enter name for Player " << i+1 << ": ";
       cin >> name;
       cout << endl; 
       g.players.push_back(new Human(g, name, true));
     }
     for (int i=humans; i<totalplayers; i++){ //creating computer players 
       name = "Player " + std::to_string(i+1);
       g.players.push_back(new Computer(g, name, false)); 
     }

     cout << "How many initial cards in the stock piles? ";
     try {
       cin >> stock;
       cout << endl; 
     } catch (int e){ //if user doesn't enter in an integer, will set to 30
       cout << "Invalid input--defaultly set to 30 cards." << endl; 
       stock = 30; 
     }
     if (stock>30 || stock<1) { //if user enters in anything above 30, will set to 30
       stock = 30;
       cout << "Invalid input--defaultly set to 30 cards." << endl;
       cout << endl;
     }
     getchar();
     g.createDeck(); //creates new deck of cards
     for (unsigned int j = 0; j < g.players.size(); j++) { //distributes hand and stock pile to every player
       g.distributeCards(*(g.players.at(j)), stock);
     }
     currentPlayer = 0;
   } else if (choice ==2){ //user would like to load game
     g.loadGame();
     totalplayers=g.players.size(); 
     //checks whose turn it is after you load game
     for (unsigned int j = 0; j<g.players.size(); j++) {
       if (g.players.at(j)->getIsMove()) {
	 currentPlayer = j;
	 break;
       }
     }
   }
  
   //loop that goes through takeTurn function for all the players
   //loop only ends if one of the players wins or if the player wants to save
   do {
     cout << g.players.at(currentPlayer)->getName() << "'s turn:" << endl;
     g.players.at(currentPlayer)->takeTurn();
     if(g.players.at(currentPlayer)->getWinGame() || g.players.at(currentPlayer)->getSave()) {
       break;
     }
     if (currentPlayer==totalplayers-1){
       currentPlayer = 0;
     } else {
       currentPlayer++; //loops through all of the players
     }
   } while (!g.players.at(currentPlayer)->getWinGame() && !g.players.at(currentPlayer)->getSave()) ;
   
   //if players wins, outputs congratulations
   //if player saves, saves game and quit
   if(g.players.at(currentPlayer)->getWinGame()){
     cout << "Congratulations, " << g.players.at(currentPlayer)->getName() << ", you won!" << endl; 
   } else {
     cout << "Game saved. Goodbye!"<< endl;
   }

   for (int i = 0; i<totalplayers; i++) {
     delete g.players.at(i);
   }
   delete gptr; 
   exit(0); 
}
