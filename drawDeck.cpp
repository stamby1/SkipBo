#include "drawDeck.h"

//shuffles the drawdeck with random integers
void drawDeck::shuffle(){
  srand(time(NULL));
  vector<Card> tempPile;
  int count = this->cards.size();
  for(int i=0; i<count; i++) {
    int random = rand()%this->cards.size();
    tempPile.push_back(this->cards.at(random));
    this->cards.erase(this->cards.begin()+random);
  }
  this->cards = tempPile;
}
