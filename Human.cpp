#include "Human.h"
#include <cctype>
#include <cstdio>
#define ASCII_LOC 48

//returns true if someone wins, returns false if the player completed it's turn (cannot make any more valid moves)
void Human::takeTurn() {
  if(game.draw->cards.size() < 5 - hand->cards.size())
    game.fillDrawDeck();
  hand->update(*game.draw);
  isMove = true;
  string input;
  while(isMove) {
    game.printCurrentPlayersInfo(*this);
    for(unsigned int i =0; i< game.players.size(); i++) {
      if (game.players.at(i) != this) {
	game.printOtherPlayersInfo(*(game.players.at(i)));
      }
    }
    std::cout << "Enter your move or 'S' to save and quit: ";
    std::getline(std::cin, input);
    makeMove(input);
    if(input == "S" || input == "s"){
      return; 
    }
    if (this->stock->win()) {
      winGame=true;
      isMove = false;
    }
  }
}

//returns false if the move the player wanted to make is invalid, returns true if the player finished it's move successfully
bool Human::makeMove(string move) {
  //user asks to Save Game by typing S
  if(move == "S" || move == "s") {
    game.saveGame();
    save = true; 
    return true;
  }

  char source = toupper(move.at(0));
  //invalid move, then return move because need to use card 
  //from either hand, stock, or discard pile 
  if(source != 'H' && source != 'S' && source != 'D') {
    std:: cout << "Invalid move. Source card needs to be from H, S, or D." << std::endl ; 
    return false;
  }
  int cardLoc = 0, pos = 2;
  //cardLoc is the SOURCE pile number
  if(source != 'S') {
    cardLoc = move.at(1)-ASCII_LOC;
    if (cardLoc <=0 || cardLoc >5){
    std:: cout << "Invalid move. Pile/Card position needs to be 1-5. " << std:: endl;
    return false; 
    }
    pos++;
  }

  
    std::cout << std::endl;

  //takes destination pile letter 
  char dest = toupper(move.at(pos));
  //if not buildingPile or discard pile as destination, invalid move
  if(dest != 'B' && dest != 'D') {
    std:: cout << "Invalid move. Destination card needs to be to B or D." << std:: endl; 
    std::cout << std::endl;
    return false;
  }
  //pileNum is the DESTINATION pile num
  int pileNum=0;
  try {
    pileNum = move.at(pos+1)-ASCII_LOC; 
    //returns false if the pile number of the destination is invalid
  } catch(int e) {
    std:: cout << "Invalid move. Destination # is wrong. " << std::endl;
    std::cout << std::endl;
    return false;     
  }

  if (pileNum <=0 || pileNum >4){
    std:: cout << "Invalid move. Destination pile position needs to be 1-4. " << std:: endl; 
    std::cout << std::endl;
    return false;
  }

  if(dest == 'B') {
    if(source == 'H') { //if user wishes to put hand card to buildingPile
      return addBuilding(hand->cards.at(cardLoc-1), *game.buildPiles[pileNum-1], source, cardLoc);
    }
    if(source == 'S') { //user wishes to add stock card to buildingPile
      return addBuilding(stock->cards.at(0), *game.buildPiles[pileNum-1], source, cardLoc);
    }
    if(source == 'D') { //user wishes to add discard pile to buildingPile
      if (discard[cardLoc-1]->cards.empty()) {
	std::cout << "Invalid move. This discard pile is empty." << std::endl;
	std::cout<<std::endl;
	return false;
      } else {
	return addBuilding(discard[cardLoc-1]->cards.at(0), *game.buildPiles[pileNum-1], source, cardLoc);
      }
    }
  }

  if(dest == 'D') { 
    if(source != 'H') { //user wishes to put hand card to discard pile
      std:: cout << "Invalid move. You can only put a hand card to discard pile. " << std:: endl; 
    std::cout << std::endl;
      return false;
    } else {
      addDiscard(hand->cards.at(cardLoc-1), pileNum); 
    }
  }
  return true;
}
