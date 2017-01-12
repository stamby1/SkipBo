#include "Players.h"
#include "Human.h"
#include "Computer.h"
#include "Game.h"
#include "Pile.h" 
#include "Card.h" 
#include "Stock.h"
#include "drawDeck.h"
#include "buildingPile.h" 
#include <iostream>
#include <vector>
#include <string>
#include <cassert> 

using std::string; 
using std::endl;
using std::cout; 

class playersTest{
public:
  static void constructorTest(){
    Game *gptr = new Game(); 
    Game &g = *gptr; 

    Human *p1ptr = new Human(g, "AmySharmila", true);
    Human &p1 = *p1ptr;
    assert(p1.getName() == "AmySharmila");
    assert(p1.hand->getSize()==0);
    assert(p1.stock->getSize()==0);

    Human *p2ptr = new Human(g, "Eric Tony", true);
    Human &p2 = *p2ptr;
    assert(p2.getName() == "Eric Tony");
    assert(p1.hand->getSize()==0);
    assert(p1.stock->getSize()==0);

    delete gptr; 
    delete p1ptr;
    delete p2ptr; 
    
  }

  static void getNameTest() {
    Game *gptr = new Game();
    Game &g = *gptr;

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;
    assert(h.getName()=="Amy");

    Human *h2ptr = new Human(g, "Eric", true);
    Human &h2 = *h2ptr;
    assert(h2.getName()!="Amy");
    assert(h2.getName()=="Eric");

    Human *h3ptr = new Human(g, "Tony", true);
    Human &h3 = *h3ptr;
    assert(h3.getName()!="Eric");
    assert(h3.getName()!="Amy");
    assert(h3.getName()=="Tony");

    Human *h4ptr = new Human(g, "Sharmila", true);
    Human &h4 = *h4ptr;
    assert(h4.getName()!="Amy");
    assert(h4.getName()!="Eric");
    assert(h4.getName()!="Tony");
    assert(h4.getName()=="Sharmila");

    delete gptr;
    delete hptr;
    delete h2ptr;
    delete h3ptr;
    delete h4ptr;

  }

  static void addBuildingTest(){
    Card c0 (0); //0 is a SkipBo card 
    Card c1 (1);
    Card c2 (2);
    Card c3 (3);
    Card c4 (4);
    Card c5 (5);
    Card c6 (6);
    Card c7 (7);
    Card c8 (8);
    Card c9 (9);
    Card c10(10);
    Card c11(11);
    Card c12(12);

    Game *gptr = new Game(); 
    Game &g = *gptr; 
    Human *p1ptr = new Human(g, "AmySharmila", true);
    Human &p1 = *p1ptr;
    
    //currently, the game's building pile is 1, 2, 3
    vector<Card> v = {c3, c2, c1};
    buildingPile &bp1 = *g.buildPiles[0];
    bp1.cards.insert(bp1.cards.begin(), v.begin(), v.end());
    assert(bp1.getSize() == 3); 
    
    //hand's pile is 4, SkipBo, 7, 9 
    vector<Card>v2 = {c4, c0, c7, c9};
    Hand &h = *p1.hand; 
    h.cards.insert(h.cards.begin(), v2.begin(), v2.end()); 
    //stock's pile is SkipBo, 8
    vector<Card>v2a = {c0, c8};
    Stock &s = *p1.stock; 
    s.cards.insert(s.cards.begin(), v2a.begin(), v2a.end()); 
    
    //first discard's pile is 5, 1
    vector<Card>v3 = {c5, c1};
    Pile &d = *p1.discard[0];
    d.cards.insert(d.cards.begin(), v3.begin(), v3.end());
    
    assert(!p1.addBuilding(c7, bp1, 'H', 3));
    assert(h.getSize()==4); 
    assert(!p1.addBuilding(c9, bp1, 'H', 4));
    assert(h.getSize()==4); 
    assert(h.flipTop()==4); 
    assert(bp1.getSize()==3); 
    //adds c4 to building pile from hand pile accurately
    assert(p1.addBuilding(c4, bp1, 'H', 1));
    assert(h.getSize()==3); //hand size decreases by 1
    assert(h.flipTop()==0); 
    assert(bp1.getSize()==4); //building pile size increase by 1; 
    
    assert(!p1.addBuilding(c1, bp1, 'D', 2));
    assert(d.getSize()==2); 
    //adds c5 to building pile from discard pile accurately 
    assert(p1.addBuilding(c5, bp1, 'D', 1));
    assert(d.getSize()==1); 
    assert(bp1.getSize()==5); 

    //adds skipbo card to building pile froms stock pile accurately
    assert(p1.addBuilding(c0, bp1, 'S', 0));
    assert(s.getSize()==1); 
    assert(bp1.getSize()==6); 
    assert(!p1.addBuilding(c8, bp1,'S', 0));
    assert(s.getSize()==1);
    assert(bp1.getSize()==6); 

    //adds c7 to building pile ron hand pile accurately
    assert(p1.addBuilding(c7, bp1, 'H', 2)); 
    assert(h.getSize()==2);
    assert(bp1.getSize()==7); 
    assert(p1.addBuilding(c8, bp1, 'S', 0));
    assert(s.cards.empty());//check stock pile is now empty
    assert(bp1.getSize()==8); 
    
    assert(p1.hand->getSize()==2); 
    assert(p1.hand->flipTop()==0); 
    assert(p1.stock->cards.empty());
    assert(p1.discard[0]->getSize()==1); 
    assert(g.buildPiles[0]->getSize()==8); 

    delete gptr; 
    delete p1ptr;
  } 

  static void addDiscardTest() {

    Game *gptr = new Game();
    Game &g = *gptr;

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;

    Card c0 (0);
    Card c1 (1);
    Card c2 (2);
    Card c3 (3);
    Card c4 (4);
    Card c5 (5);
    Card c6 (6);
    Card c7 (7);
    Card c8 (8);
    Card c9 (9);

    vector<Card> v = {c0, c1, c2, c3, c4};
    h.hand->cards.insert(h.hand->cards.begin(), v.begin(), v.end());

    h.addDiscard(c1, 1); //add c1 to Amy's 1st discard pile
    assert(h.hand->getSize()!=5);
    assert(h.hand->getSize()==4);
    assert(h.discard[0]->getSize()==1);
    assert(h.discard[0]->flipTop()==1);
    assert(h.discard[1]->getSize()==0);
    assert(h.discard[2]->getSize()==0);
    assert(h.discard[3]->getSize()==0);

    h.addDiscard(c4, 1); //add c4 to Amy's 1st discard pile
    assert(h.hand->getSize()!=4);
    assert(h.hand->getSize()==3);
    assert(h.discard[0]->getSize()==2);
    assert(h.discard[0]->flipTop()==4);
    assert(h.discard[1]->getSize()==0);
    assert(h.discard[2]->getSize()==0);
    assert(h.discard[3]->getSize()==0);


    Human *h2ptr = new Human(g, "Sharmila", true);
    Human &h2 = *h2ptr; 
    vector<Card> v2 = {c5, c6, c7, c8, c9};
    h2.hand->cards.insert(h2.hand->cards.begin(), v2.begin(), v2.end());

    h2.addDiscard(c5, 3); //add c2 to Sharmila's 3rd discard pile
    assert(h2.hand->getSize()!=5);
    assert(h2.hand->getSize()==4);
    assert(h2.discard[2]->getSize()==1);
    assert(h2.discard[2]->flipTop()==5);
    assert(h2.discard[0]->getSize()==0);
    assert(h2.discard[1]->getSize()==0);
    assert(h2.discard[3]->getSize()==0);

    h2.addDiscard(c9, 1); //add c9 to Sharmila's 1st discard pile
    assert(h2.hand->getSize()!=4);
    assert(h2.hand->getSize()==3);
    assert(h2.discard[0]->getSize()==1);
    assert(h2.discard[0]->flipTop()==9);
    assert(h2.discard[1]->getSize()==0);
    assert(h2.discard[2]->getSize()==1);
    assert(h2.discard[3]->getSize()==0);

    delete gptr;
    delete hptr;
    delete h2ptr;
  }

  static void refillCardTest() {

    Card c0 (0);
    Card c1 (1);
    Card c2 (2);
    Card c3 (3);
    Card c4 (4);
    Card c5 (5);
    Card c6 (6);
    Card c7 (7);
    Card c8 (8);
    Card c9 (9);
    Card c10 (10);
    Card c11 (11);
    Card c12 (12);

    Game *gptr = new Game();
    Game &g = *gptr;
    vector<Card> v = {c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};\

    g.draw->cards.insert(g.draw->cards.begin(), v.begin(), v.end());

    Human *hptr = new Human(g, "Eric", true);
    Human &h = *hptr;
    assert(h.hand->getSize()==0);
    assert(g.draw->getSize()==13);

    h.refillCard(); //takes 5 cards from drawDeck and adds them to hand
    assert(h.hand->getSize()==5);
    assert(g.draw->getSize()==8);

    Human *h2ptr = new Human(g, "Tony", true);
    Human &h2 = *h2ptr;
    vector<Card> v2 = {c1, c2, c3};
    h2.hand->cards.insert(h2.hand->cards.begin(), v2.begin(), v2.end());
    assert(h2.hand->getSize() == 3);

    h2.refillCard(); //should not add more cards to hand because hand is not empty
  assert(h2.hand->getSize() == 3);
 assert(g.draw->getSize() == 8); //size of draw deck does not change

 delete gptr;
 delete hptr;
 delete h2ptr;

  }

  static void makeMoveTest() {

    Card c0 (0);
    Card c1 (1);
    Card c2 (2);
    Card c3 (3);
    Card c4 (4);
    Card c5 (5);
    Card c6 (6);
    Card c7 (7);
    Card c8 (8);
    Card c9 (9);
    Card c10 (10);
    Card c11 (11);
    Card c12 (12);

    Game *gptr = new Game();
    Game &g = *gptr;
    vector<Card> v = {c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
    g.draw->cards.insert(g.draw->cards.begin(), v.begin(), v.end());

    Human *hptr = new Human(g, "AmySharmila", true);
    Human &h = *hptr;
    assert(h.hand->getSize()==0);
    assert(g.draw->getSize()==13);
    vector <Card> sampleHand = {c0, c1, c11, c2, c4};
    vector <Card> sampleStock = {c3, c0, c6, c5, c10};
    h.hand->cards.insert(h.hand->cards.begin(), sampleHand.begin(), sampleHand.end());
    h.stock->cards.insert(h.stock->cards.begin(), sampleStock.begin(), sampleStock.end());
    assert(h.hand->getSize()==5);
    assert(h.stock->getSize()==5);
    
    assert(!h.makeMove("q1 B1")); //invalid source
    
    //TESTS for addBuilding, source Hand
    assert(h.makeMove("H2 B2"));
    assert(h.hand->getSize()==4);
    assert(g.buildPiles[1]->getSize()==1);
    assert(g.buildPiles[1]->flipTop()==1);
    
    //Current hand: {c0, c11, c2, c4}
    //Current BP2: {c1}
    assert(!h.makeMove("h2 b2")); //h2 is now c11, can't be added to BP2

    assert(h.makeMove("h1 b2")); //adds a skipbo card to buildPile2
    assert(h.hand->getSize()==3);
    assert(g.buildPiles[1]->getSize()==2);
    assert(g.buildPiles[1]->flipTop()==2);

    //Current hand: {c11, c2, c4}
    //Current BP2: {c1, c2}
    assert(!h.makeMove("h1 B1")); //h1 is c11, can't be first card in BP
    
    //TESTS for addBuilding, source Stock
    h.makeMove("S b2");
    assert(h.stock->getSize()==4);
    assert(g.buildPiles[1]->getSize()==3);
    assert(g.buildPiles[1]->flipTop()==3);

    h.makeMove("S B3"); //adds a skipbo card to buildPile3
    assert(h.stock->getSize()==3);
    assert(g.buildPiles[2]->getSize()==1);
    assert(g.buildPiles[2]->flipTop()==1);

    //Current stock: {c6, c5, c10}
    //Current BP2: {c1, c2, c3}, Current BP3: {c0}
    assert(!h.makeMove("s b2")); //can't add c6 to BP2

    //TESTS for addDiscard, source Hand
    h.makeMove("H3 d1");
    assert(h.hand->getSize()==2);
    assert(h.discard[0]->getSize()==1);
    assert(h.discard[0]->flipTop()==4);

    //TESTS for addBuilding, source Discard
    h.makeMove("D1 b2");
    assert(h.discard[0]->getSize()==0);
    assert(g.buildPiles[1]->getSize()==4);
    assert(g.buildPiles[1]->flipTop()==4);
    
    delete gptr;
    delete hptr;
  }

  static void getSaveTest() {
    Game *gptr = new Game(); 
    Game &g = *gptr; 

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;

    Computer *cptr = new Computer(g, "EricTony", false);
    Computer &c = *cptr;

    Human *h2ptr = new Human(g, "Sharmila", true);
    Human &h2 = *h2ptr;
    h2.save=true;

    assert(!h.getSave());
    assert(!c.getSave());
    assert(h2.getSave());

    delete gptr;
    delete hptr;
    delete cptr;
    delete h2ptr;

  }

  static void getIsMoveTest() {
    Game *gptr = new Game(); 
    Game &g = *gptr; 

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;

    Computer *cptr = new Computer(g, "EricTony", false);
    Computer &c = *cptr;
    c.isMove = true;

    assert(!h.getIsMove());
    assert(c.getIsMove());

    delete gptr;
    delete hptr;
    delete cptr;
  }

  static void getWinGameTest() {
    Game *gptr = new Game(); 
    Game &g = *gptr; 

    Human *hptr = new Human(g, "Amy", true);
    Human &h = *hptr;

    Computer *cptr = new Computer(g, "EricTony", false);
    Computer &c = *cptr;
    c.winGame = true;

    assert(!h.getWinGame());
    assert(c.getWinGame());
    delete gptr; 
    delete hptr; 
    delete cptr; 
  }

};

int main(void){
  cout << "Running Players test..." << endl;
  playersTest::constructorTest();
  playersTest::getNameTest();
  playersTest::addBuildingTest();
  playersTest::addDiscardTest();
  playersTest::refillCardTest(); 
  playersTest::makeMoveTest();
  playersTest::getSaveTest();
  playersTest::getIsMoveTest();
  playersTest::getWinGameTest();
  cout << "Players tests passed." << endl; 
}
