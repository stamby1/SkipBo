#include "Players.h"

Players::Players(Game &g, string n, bool isHuman): name(n), game(g), isHuman(isHuman) {
  stock = new Stock();
  hand = new Hand();
  for (int i=0; i<4; i++){
    discard[i]= new Pile();
  }
  winGame=false; 
}

//deconstructor for players 
Players:: ~Players(){
  delete stock; 
  delete hand; 
  for (int i=0; i<4; i++){
    delete discard[i];
  }
}

//true if players wants to save game 
bool Players::getSave(){
  return save;
}

//true if players already won 
bool Players:: getWinGame(){
  return winGame; 
}

//return true if player was able to addBuilding
//adds specified card to building pile
//source is h,s,d and cardLoc is the pileNum of where the card is from 
bool Players:: addBuilding(Card card, buildingPile &pile, char source, int cardLoc) {
  //adds to the buildingPile
  int pileTop = 0; 
  if (!pile.cards.empty()){
    pileTop =  pile.flipTop();
  }
  if (card.isSB()){ //if the card is SkipBo, change value of the card to +1 of the top card of buildingPile
    card.changeValue(pileTop+1);
  }
  if (card.getValue() != (pileTop+1)){ 
    std:: cout << "Invalid move. Card value cannot be added to this building pile. " << std:: endl;
    std::cout << std::endl;
    return false;
  }
    
  pile.cards.insert(pile.cards.begin(), card);
  //if the source is from the hand pile, delete the card from the hand pile

  //AMY'S QUESTION: cardLoc already has the location so no need for loop to find the card?
  if (source == 'H') {
    hand->cards.erase(hand->cards.begin()+(cardLoc-1));   
		      
    //checks if the hand is empty 
    refillCard();
    //if the source is from the stock pile, delete the card from the discard pile
    //already checked whether stock's top card is found in getMove();
  
    

  } else if (source == 'S') {
    stock->cards.erase(stock->cards.begin());
  
    //if the source is from the discard pile, delete the card from the discard pile
    //already checked the user's destination discard pile has the card in getMove();
  } else if (source == 'D') {
    discard[cardLoc-1]->cards.erase(discard[cardLoc-1]->cards.begin());
  }

  //call the emptyPile when it reaches 12                                                          
  if(pile.getSize() == 12){
    pile.emptyPile();
  }
  
  
  return true; 
  
}

//adds specified card to a discard pile num 
void Players:: addDiscard(Card card, int num) {
  discard[num-1]->cards.insert(discard[num-1]->cards.begin(), card);
  for(unsigned int i=0; i<hand->cards.size(); i++) {
    if(hand->cards.at(i) == card) {
      hand->cards.erase(hand->cards.begin()+i);
      break;
    }
  }
  isMove = false;
}

string Players:: getName() {
  return name;
}

//at a new turn, if player doesn't have 5 cards, add cards from drawDeck 
void Players::refillCard(){
  if(game.draw->cards.size() < 5){
    game.draw->cards.insert(game.draw->cards.end(),game.getTempPile().cards.begin(),game.getTempPile().cards.end());
  }
  if(hand->getSize() == 0){
    for(int i = 0; i < 5; i++){
      hand->cards.push_back(game.draw->getCard());
    }
  }
}

//if it is currently player's move, return true 
bool Players::getIsMove() {
  return isMove;
}
