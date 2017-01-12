#ifndef _SKIPBO_GAME_H
#define _SKIPBO_GAME_H
#include "Players.h"
#include "buildingPile.h"
#include "drawDeck.h"
#include <fstream>
using std::string;

class Players;
class Game {
  friend int main();
  friend class Players;
  friend class Human;
  friend class Computer;
  friend class playersTest;
  friend class gameTest;
 private:
  void createDeck();
  void distributeCards(Players &player, int numStock);
  vector<Players*> players;
  bool createSavedFile(string gameName);
  std::string saveString();
  void loadHelper(std::ifstream &infile);
  Card stringToCard(string num);
 protected:
  drawDeck *draw;
  drawDeck *tempPile = new drawDeck();
  buildingPile *buildPiles[4];
  drawDeck getTempPile();
  void fillDrawDeck();
public:
  Game();
  ~Game();
  void printOtherPlayersInfo(Players &p);
  void printCurrentPlayersInfo(Players &p);
  void saveGame();
  void loadGame();
  void quitGame();
};

#endif
