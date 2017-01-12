#ifndef _PLAYERS_H
#define _PLAYERS_H
#define DEF_CARD_NUM 30
#include "Game.h"
#include "Pile.h"
#include "Hand.h"
#include "Stock.h"
#include "buildingPile.h"
#include <string>
#include <vector>
#include <cstdbool>
using std::vector;
using std::string;
class Game;
class Players {
  friend class Game;
  friend class gameTest;
  friend class playersTest;
 protected:
  string name;
  bool save = false; 
  Hand *hand;
  Stock *stock;
  Pile *discard[4];
  Game &game;
  void refillCard();
  bool isMove;
  bool isHuman;
  bool winGame; 
 public:
  string getName();
  bool getSave(); 
  Players(Game &g, string n="", bool isHuman = false);
  virtual ~Players(); 
  virtual void takeTurn() = 0;
  bool addBuilding(Card card, buildingPile &pile, char source, int pileNum);
  void addDiscard(Card card, int num);
  bool getIsMove();
  bool getWinGame(); 
  
};

#endif
