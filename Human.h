#ifndef _HUMAN_H
#define _HUMAN_H
#include "Game.h"
#include "Players.h"
#include "Stock.h" 
#include "buildingPile.h"
#include <iostream>
#include <fstream>
using std::ofstream;

class Human : public Players{
  friend class playersTest; 
  friend class gameTest;
 
 public:
 Human(Game &g, string n, bool isHuman): Players(g, n, isHuman){};
  void takeTurn();
  bool makeMove(string move);
};

#endif
