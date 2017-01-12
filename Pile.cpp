#include "Pile.h"

Pile::Pile() { }

//gives us the value of the card in the top
int Pile::flipTop(){
  return this->cards.at(0).getValue();
}

//returns the value of the Card on the otp of the deck
//deletes it and reduces the size
Card Pile::getCard(){
  Card card = this->cards.at(0);
  this->cards.erase(this->cards.begin());
  return card;
}

//Gets the size of the cards.
//Can be stock, hand, discardpile etc...
int Pile::getSize(){
  return this->cards.size();
}
