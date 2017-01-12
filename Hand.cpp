#include "Hand.h"

//draws card from drawDeck depending on hwo many cards already are in hand
void Hand::update(drawDeck &drawDeck){
  
  for(int i = this->getSize(); i < 5; i++){
    this->cards.push_back(drawDeck.getCard());
  }
}
