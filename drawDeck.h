#ifndef _DRAWDECK_H
#define _DRAWDECK_H
#include "Pile.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class drawDeck : public Pile
{
  friend class Game;
  friend class pileTest; 
 public:

 drawDeck() : Pile(){};
  void shuffle();
};
#endif
