#ifndef _PILE_H
#define _PILE_H
#include "Card.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;

class Pile
{
  friend class Game;
  friend class Players;
  friend class Human;
  friend class Computer;
  friend class pileTest;
  friend class playersTest; 
  friend class gameTest; 
 public:
  Pile(); //default constructor
  Card getCard(); 
  int getSize(); //returns the size

 protected:
  int flipTop(); //returns the value of the top of the card
  vector<Card> cards; //vector of cards

};

#endif
