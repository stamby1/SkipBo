#ifndef _HAND_H
#define _HAND_H
#include "Pile.h"
#include "drawDeck.h"
#include <iostream>
#include <string>
#include <vector>

class Hand : public Pile
{
  friend class Game;
  friend class Players;
  friend class Human;
  friend class Computer;
  friend class pileTest; 
 private:
  int numHands=0;
  void update(drawDeck &drawDeck);
 public:
 Hand(): Pile (){};
 Hand(int cards) : Pile() {numHands = cards;};
};

#endif
