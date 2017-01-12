#include "Players.h"
#include "Human.h"
#include "Computer.h"
#include "Game.h"
#include "Pile.h"
#include "Card.h"
#include "Stock.h"
#include "Hand.h"
#include "buildingPile.h"
#include "drawDeck.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::string;
using std::endl;
using std::cout;

class gameTest{
public:
  static void createDeckTest() {
    Game *gptr = new Game();
    Game &g = *gptr;

    assert(g.draw->getSize()==0);

    g.createDeck();
    assert(g.draw->getSize()==162);

    delete gptr;

  }

  static void distributeCardsTest(){
    Game *gptr = new Game();
    Game &g = *gptr;

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;
    Human *h2ptr = new Human(g, "Tony", true);
    Human &h2 = *h2ptr;
    
    //creates 162 cards and shuffles them
    g.createDeck();

    g.distributeCards(h, 15);
    assert(g.draw->getSize()==142);
    assert(h.hand->getSize()==5);
    assert(h.stock->getSize()==15);

    g.distributeCards(h2, 30);
    assert(g.draw->getSize()==107);
    assert(h2.hand->getSize()==5);
    assert(h2.stock->getSize()==30);

    delete hptr;
    delete h2ptr;
    delete gptr;
    
  }

  static void fillDrawDeckTest() {
    Game *gptr = new Game();
    Game &g = *gptr;

    assert(g.draw->getSize()==0);
    assert(g.tempPile->getSize()==0);

    g.fillDrawDeck();
    assert(g.draw->getSize()==162);

    delete gptr;
    
  }

};

int main(void){
  cout << "Running Game tests..." << endl;
  gameTest::createDeckTest();
  gameTest::distributeCardsTest();
  gameTest::fillDrawDeckTest();
  cout << "Game tests passed." << endl;
}


