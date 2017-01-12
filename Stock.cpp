#include "Stock.h"

//checks if the number of cards in the player's stock pile is empty, if so, then they win
bool Stock:: win(){
  if (this->getSize()==0){
    return true;
  }
  return false;
}
