#ifndef _COMPUTER_H
#define _COMPUTER_H
#include "Players.h"

class Computer : public Players {

 public:
 Computer(Game &g, string n, bool isHuman) : Players(g, n, isHuman) {};
  void takeTurn();
};

#endif
