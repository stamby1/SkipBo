#include "Computer.h"

//Artificial Intelligence for the computer (described in README)
void Computer::takeTurn() {

  if(stock->win()) { //checks to see if computer has won
    winGame = true;
    return;
  }
  
  static bool firstMove = true;
  if(firstMove) {
    std::cout << "Computer is moving..." << std::endl << std::endl;
    if(game.draw->cards.size() < 5 - hand->cards.size())
      game.fillDrawDeck();
    hand->update(*game.draw);
    firstMove = false;
  }
  
  for(int i=0; i<4; i++) { //first checks if the stock card can be played to any building piles
    if(game.buildPiles[i]->cards.empty()) {
      if(stock->flipTop() == 1 || stock->flipTop() == 0) {
	addBuilding(stock->cards.at(0), *game.buildPiles[i], 'S', 0); //if so, calls addBuilding
	takeTurn(); //and recurses to check again
	return;
      }
    } else if (game.buildPiles[i]->flipTop() == stock->flipTop()-1 || stock->flipTop() == 0) {
      addBuilding(stock->cards.at(0), *game.buildPiles[i], 'S', 0); //if so, calls addBuilding
      takeTurn(); //and recurses to check again
      return;
    }
  }
  
  int skipBoPos = -1; //variable used as check to see if skip bo card is in hand
  int stockSetUp = -1; //variable used to see if stock card is just 2 away from the value of one of the building piles
  for(int i=0; i<4; i++) {
    for(unsigned int j=0; j<hand->cards.size(); j++) {
      if(hand->cards.at(j).getValue() == 0) { //if skipbo is present, this saves location in hand
	skipBoPos = j;
      }
      if(game.buildPiles[i]->cards.empty()) {
	if(hand->cards.at(j).getValue() == 1) {
	  addBuilding(hand->cards.at(j), *game.buildPiles[i], 'H', j+1); //call addBuilding
	  takeTurn(); //and recurse
	  return;
	}
      } else if(game.buildPiles[i]->flipTop() == hand->cards.at(j).getValue()-1) { //if card in hand can be played
	addBuilding(hand->cards.at(j), *game.buildPiles[i], 'H', j+1); //call addBuilding
	takeTurn(); //and recurse
	return;
      }
    }
    if(game.buildPiles[i]->cards.empty()) {
      if(stock->flipTop() == 2) {
	stockSetUp = i;
      }
    } else if(game.buildPiles[i]->flipTop() == stock->flipTop()-2) { //if stock card is just 2 away from building pile, make note of this
      stockSetUp = i;
    }
  }
  
  if(skipBoPos != -1) { //if skip bo card is present in hand
    if(stockSetUp != -1) { //if stock card is 2 away from building pile
      addBuilding(hand->cards.at(skipBoPos), *game.buildPiles[stockSetUp], 'H', skipBoPos+1); //play to this specific building pile
    } else { //otherwise just play the skip bo card to the first building pile
      addBuilding(hand->cards.at(skipBoPos), *game.buildPiles[0], 'H', skipBoPos+1);
    }
    takeTurn(); //and recurse
    return;
  }
  
  int disSkipPos = -1; //this variable saves position of skip bo card in discard piles
  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(!(discard[j]->cards.empty())) {
	if(game.buildPiles[i]->cards.empty()) {
	  if(discard[j]->flipTop() == 1) {
	    addBuilding(discard[j]->cards.at(0), *game.buildPiles[i], 'D', j+1); //addBuilding is called
	    takeTurn(); //and the function recurses
	    return;
	  }
	} else if(game.buildPiles[i]->flipTop() == discard[j]->flipTop()-1) { //if discard pile card can be played
	  addBuilding(discard[j]->cards.at(0), *game.buildPiles[i], 'D', j+1); //addBuilding is called
	  takeTurn(); //and the function recurses
	  return;
	}
	if(discard[j]->flipTop() == 0) { //if there is a skipbo card in one of the discard piles
	  disSkipPos = j; //save its location
	}
      }
    }
  }
  
  if(disSkipPos != -1) { //if there is a skipbo card in the discard piles
    if(stockSetUp != -1) { //and if stock card is 2 away from building pile
      addBuilding(discard[disSkipPos]->cards.at(0), *game.buildPiles[stockSetUp], 'D', disSkipPos+1); //play the discard skip bo card to this specific building pile
    } else { //otherwise, just play it to the first building pile
      addBuilding(discard[disSkipPos]->cards.at(0), *game.buildPiles[0], 'D', disSkipPos+1);
    }
    takeTurn(); //and recurse
    return;
  }
  //if none of the cards from stock,hand,or discard can be added to building pile, prepare to add card in hand to discard pile
  int disPos = 0; //keeps track of location of most empty discard pile
  unsigned int size = discard[disPos]->cards.size();
  for(int i=1; i<4; i++) { //if one of the discard piles has less cards, save this
    if(discard[i]->cards.size() < size) {
      disPos = i;
    }
  }
  
  int handPos = 0; //keeps track of the hand card highest valued above the skip bo card
  for(unsigned int i=1; i<hand->cards.size(); i++) { //if the hand card is greater than the stock card, and its greater than the one currently being kept track of,
    if(hand->cards.at(i).getValue() > stock->flipTop() && hand->cards.at(i).getValue() > hand->cards.at(handPos).getValue()) {
      handPos = i; //then save this position
    }
  }
  
  addDiscard(hand->cards.at(handPos), disPos+1); //add the decided hand card to the decided discard pile
  firstMove = true; //reset static variable
  return; //and end the function
}
