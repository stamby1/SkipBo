#ifndef _STOCK_H
#define _STOCK_H
#include "Pile.h"

class Stock : public Pile
{
  friend class Game;
  friend class pileTest;
  friend class playersTest; 
 public:
  Stock() : Pile() {};
  bool win();
};

#endif
