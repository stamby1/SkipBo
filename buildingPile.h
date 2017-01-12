#ifndef _BUILDING_PILE_H
#define _BUILDING_PILE_H
#include "Pile.h"
#include "drawDeck.h"
#include <iostream>
#include <vector>

class buildingPile: public Pile{
  friend class Game; 
  friend class pileTest; 
 public: 
  buildingPile(): Pile(){};
  void emptyPile();
};

#endif
