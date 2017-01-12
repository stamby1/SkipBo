#include "Game.h"
#include "Human.h"
#include "Computer.h"
#include <ostream>
#include <cstdlib>
#include <string>
#define ASCII_LOC 48

Game::Game() {
  draw = new drawDeck();
  for(int i=0; i<4; i++)
    buildPiles[i] = new buildingPile();
  //initialize players vector in main
}

Game::~Game(){
  delete draw;
  delete tempPile;
  for(int i=0; i<4; i++){
    delete buildPiles[i];
  }
}

void Game::createDeck() {
  //creates 12 sets of cards 1-12
  for(int i = 0; i<12;i++) {
    for(int j = 1; j<13; j++) {
      this->draw->cards.push_back(*(new Card(j)));
    }
  }

  //creates 18 skipbo cards
  for(int k = 0; k<18; k++) {
    this->draw->cards.push_back(*(new Card(0)));    
  }

  this->draw->shuffle();

}

void Game::distributeCards(Players &player, int numStock) {

  player.hand->cards.insert(player.hand->cards.begin(), this->draw->cards.begin(), this->draw->cards.begin()+5);
  this->draw->cards.erase(this->draw->cards.begin(), this->draw->cards.begin()+5);
  //add cards to player's stock
  player.stock->cards.insert(player.stock->cards.begin(), this->draw->cards.begin(), this->draw->cards.begin()+numStock);
  this->draw->cards.erase(this->draw->cards.begin(), this->draw->cards.begin()+numStock);
 
}

//print the other players' stock and discard piles
void Game::printOtherPlayersInfo(Players &p) {
  string name = p.getName(); 
  string stock = std::to_string(p.stock->flipTop()); 
  if (stock=="0"){
    stock = "SB";
  }
  int stocksize = p.stock-> getSize(); 
  
  std::cout << name << "'s stock card: " << stock << " (" << stocksize << " cards left)" << "    ";

  string d1="--";string d2 ="--"; string d3="--" ; string d4 = "--";
 
    if (!p.discard[0]->cards.empty()){
      d1 = std::to_string( p.discard[0]->flipTop());
      if (d1=="0") {
	d1 = "SB";
      }
    }
    if (!p.discard[1]->cards.empty()){
      d2 = std::to_string(p.discard[1]->flipTop());
      if (d2=="0"){
	d2 = "SB";
      }
    }
    if (!p.discard[2]->cards.empty()){
      d3 =std::to_string( p.discard[2]->flipTop());
      if (d3=="0"){
	d3 = "SB";
      }
    }
    if (!p.discard[3]->cards.empty()){
      d4 = std::to_string(p.discard[3]->flipTop());
      if (d4=="0"){
	d4 = "SB";
      }
    }
   std::cout<< "Discard Piles: D1: " << d1 << " | D2: " << d2 << " | D3: " << d3 << " | D4: " << d4 << std::endl;

   std::cout << std::endl; 
}

//print buildpiles and current player's info
void Game::printCurrentPlayersInfo(Players &p){
  string b1="--"; string b2 ="--" ; string b3="--";string b4 = "--";
    if (!buildPiles[0]->cards.empty()){
      b1 = std::to_string(buildPiles[0]->flipTop());
    }
    if (!buildPiles[1]->cards.empty()){
      b2 = std::to_string( buildPiles[1]->flipTop());
    }
    if (!buildPiles[2]->cards.empty()){
      b3 = std::to_string(buildPiles[2]->flipTop());
    }
    if (!buildPiles[3]->cards.empty()){
      b4 = std::to_string(buildPiles[3]->flipTop());
    }
    std::cout<< "Build Piles: B1: " << b1 << " | B2: " << b2 << " | B3: " << b3 << " | B4: " << b4 << std::endl; 
    std::cout << std::endl;
    
    string stock="--";string hand ="--"; string d1 ="--"; string d2 ="--"; string d3 ="--"; string d4 = "--"; 
    int handsize = p.hand->getSize(); //get the num of cards in hand
    std:: cout << "Your Hand Pile: H1:"; 
    if (!p.hand->cards.empty()){
       
      for(int i = 0; i< handsize; i++){ //print the cards in hand 
	if (i!=0){
	  std:: cout << " | H" << i+1 << ": ";
	 }
	hand = std::to_string(p.hand->cards.at(i).getValue());
	if (hand=="0") { //if value of card is 0, then card is SkipBo
	  hand = "SB";
	}
	std:: cout << hand; 
      }
      for(int i = handsize; i< 5; i++){ //print the cards that are empty
	hand = "--"; 
	std:: cout << " | H" << i+1 << ": ";
	std:: cout << hand; 
      }
    } else { //print empty hand pile 
       for(int i = 0; i< 5; i++){
	if (i!=0){
	  std:: cout << " | H" << i+1 << ": ";
	 }
	std:: cout << hand; 
       }
    } std:: cout << std:: endl;
    
    stock= std::to_string(p.stock->flipTop()); 
    int stocksize = p.stock-> getSize(); 
    if (stock=="0"){
      stock = "SB";
    }
    std::cout<< "Your Stock Card: " << stock << " (" << stocksize << " cards left)" << std::endl;  
    
    if (!p.discard[0]->cards.empty()){
      d1 = std::to_string(p.discard[0]->flipTop());
      if (d1=="0"){
	d1 = "SB";
      }
    }
    if (!p.discard[1]->cards.empty()){
      d2 =std::to_string( p.discard[1]->flipTop());
      if (d2=="0"){
	d2 = "SB";
      }
    }
    if (!p.discard[2]->cards.empty()){
      d3 =std::to_string(p.discard[2]->flipTop());
      if (d3=="0"){
	d3 = "SB";
      }
    }
    if (!p.discard[3]->cards.empty()){
      d4 =std::to_string( p.discard[3]->flipTop());
      if (d4=="0"){
	d4 = "SB";
      }
    }
    std::cout<< "Your Discard Piles: D1: " << d1 << " | D2: " << d2 << " | D3: " << d3 << " | D4: " << d4 << std::endl; 

    std::cout << std::endl;
      
}

void Game::saveGame() {
  string gameName;
  std::cout << "Please enter a name for the save file: " << std::endl;
  std::cin >> gameName;
  if(createSavedFile(gameName) == true){
    std::ofstream myfile;
    myfile.open(gameName);
    myfile << saveString();
    myfile.close();
  }
  else {
    std::cout << "File already exists" << std::endl;
    saveGame();
  }
}

//Format of saved info:
//# players
//Name, isHuman, isMove for each player
//All cards in hand, all cards in stock, all cards in discardpiles for each player (each card separated by one space, each pile separated by \n)
//All cards in building piles (each card separated by one space, each pile separated by \n)
//All cards in drawDeck
//All cards in tempPile
string Game::saveString(){
  string save;
  save += std::to_string(players.size()) + "\n";
  int counter = 0;
  for(unsigned int i = 0; i < players.size();i++){
    if(players.at(i)->isHuman == true){
      counter++;
    }
  }
  save += std::to_string(counter) + "\n";
  for(unsigned int i=0; i<players.size(); i++) {
    save += players.at(i)->getName() + "\n";
    if(players.at(i) -> isHuman == true){
      save+= "true\n";
    }
    else{
      save += "false\n";
    }
    //save += players.at(i)->isHuman + "\n";
    if(players.at(i)->isMove == true){
      save += "true\n";
    }
    else{
      save += "false\n";
    }
    //save += players.at(i)->isMove + "\n";
    for(unsigned int j=0; j<players.at(i)->hand->cards.size(); j++)
      save += std::to_string(players.at(i)->hand->cards.at(j).getValue()) + " ";
    save += "\n";
    for(unsigned int j=0; j<players.at(i)->stock->cards.size(); j++)
      save += std::to_string(players.at(i)->stock->cards.at(j).getValue()) + " ";
    save += "\n";
    for(int k=0; k<4; k++) {
      for(unsigned int j=0; j<players.at(i)->discard[k]->cards.size(); j++)
	save += std::to_string(players.at(i)->discard[k]->cards.at(j).getValue()) + " ";
      save += "\n";
    }
  }
  for(int i=0; i<4; i++) {
    for(unsigned int j=0; j<buildPiles[i]->cards.size(); j++)
      save += std::to_string(buildPiles[i]->cards.at(j).getValue()) + " ";
    save += "\n";
  }
  for(unsigned int i=0; i<draw->cards.size(); i++)
    save +=std::to_string( draw->cards.at(i).getValue()) + " ";
  save += "\n";
  for(unsigned int i=0; i<tempPile->cards.size(); i++)
    save += std::to_string(tempPile->cards.at(i).getValue()) + " ";
  save += "\n";
  return save;
}


void Game::loadGame() {
  string gameName;
  std::cout << "Please enter a name for the load file: " << std::endl;
  std::cin >> gameName;
  std::cin.ignore();

  if(createSavedFile(gameName) == false){
    std::ifstream infile;
    infile.open(gameName);
    loadHelper(infile);
  }
  else {
    std::cout << "File does not exist" << std::endl;
    loadGame();
  }
}

void Game::loadHelper(std::ifstream &infile) {
  string info, cardNums;
  int numPlayers,numHuman;
  infile >> numPlayers;
  infile >> numHuman;
  for(int i = 0; i < numHuman; i++){
    this->players.push_back(new Human(*this,"",true));
  }
  for(int i = 0; i < numPlayers - numHuman; i++){
    this->players.push_back(new Computer(*this,"",false));
  }
  for(int i=0; i<numPlayers; i++) {
    if(i>=numHuman) {
      infile >> info;
      info += " ";
      info += std::to_string(i+1);
      infile.ignore();
      infile.ignore();
    } else {
      infile >> info;
    }
    
    players.at(i)->name = info;
    infile >> info;
    if(info == "true")
      players.at(i)->isHuman = true;
    else
      players.at(i)->isHuman = false;
    infile >> info;
    if(info == "true")
      players.at(i)->isMove = true;
    else
      players.at(i)->isMove = false;
    infile.ignore();
    std::getline(infile, info);
    for(unsigned int j=0; j<info.size(); j++) {
      while(info.at(j) != ' ') {
	cardNums += info.at(j++);
      }
      players.at(i)->hand->cards.push_back(stringToCard(cardNums));
      cardNums = "";
    }
    std::getline(infile, info);
    for(unsigned int j=0; j<info.size(); j++) {
      while(info.at(j) != ' ') {
	cardNums += info.at(j++);
      }
      players.at(i)->stock->cards.push_back(stringToCard(cardNums));
      cardNums = "";
    }
    for(int k=0; k<4; k++) {
      std::getline(infile, info);
      for(unsigned int j=0; j<info.size(); j++) {
	while(info.at(j) != ' ') {
	  cardNums += info.at(j++);
	}
	players.at(i)->discard[k]->cards.push_back(stringToCard(cardNums));
	cardNums = "";
      }
    }
  }
  for(int k=0; k<4; k++) {
    std::getline(infile, info);
    for(unsigned int j=0; j<info.size(); j++) {
      while(info.at(j) != ' ') {
	cardNums += info.at(j++);
      }
      buildPiles[k]->cards.push_back(stringToCard(cardNums));
      cardNums = "";
    }
  }
  std::getline(infile, info);
  for(unsigned int i=0; i<info.size(); i++) {
    while(info.at(i) != ' ') {
      cardNums += info.at(i++);
    }
    draw->cards.push_back(stringToCard(cardNums));
    cardNums = "";
  }
  std::getline(infile, info);
  for(unsigned int i=0; i<info.size(); i++) {
    while(info.at(i) != ' ') {
      cardNums += info.at(i++);
    }
    tempPile->cards.push_back(stringToCard(cardNums));
    cardNums = "";
  }
}

Card Game::stringToCard(string num) {
  int cardNum = std::stoi(num);
  Card *card = new Card(cardNum);
  return *card;
}

void Game::quitGame() {
  exit(0);
}

bool Game::createSavedFile(string gameName){
  if (std::ifstream(gameName)){
    return false;
  }
  else{
    return true;
  }
}

drawDeck Game::getTempPile() {
  tempPile->shuffle();
  return *tempPile;
}

void Game::fillDrawDeck() {
  if (tempPile->getSize() == 0) {
    createDeck();
  }
  else {
    draw->cards.insert(draw->cards.end(),getTempPile().cards.begin(),getTempPile().cards.end());
  }
}
