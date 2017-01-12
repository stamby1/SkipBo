#include "buildingPile.h"

//erases all of the cards in the building pile (this occurs when the building pile has reached 12)
void buildingPile:: emptyPile(){
  this->cards.erase(this->cards.begin(),this->cards.end());
}
