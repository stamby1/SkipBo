#include "Pile.h" 
#include "Card.h" 
#include "buildingPile.h"
#include "drawDeck.h"
#include "Hand.h"
#include "Stock.h" 
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::string; 
using std::endl;
using std::cout; 

class pileTest {
public: 
  static void cardTest(){

  //test constructor
  Card c1 (5); //changes to 6
  Card c2 (7); 
  Card c3 (0); //changes to 11
  Card c4 (12);
  Card c5 (1); //changes to 5
  Card c6 (2);

  //test getValue()
  assert(c1.getValue()==5);
  assert(c2.getValue()==7);
  assert(c3.getValue()==0);
  assert(c4.getValue()==12);
  assert(c5.getValue()==1);
  assert(c6.getValue()==2);
  assert(c1.getValue()!=7);
  assert(c5.getValue()!=0);

  //test isSB()
  assert(!c1.isSB());
  assert(!c2.isSB());
  assert(c3.isSB());
  assert(!c4.isSB());
  assert(!c5.isSB());
  assert(!c6.isSB());

  //test changeValue()
  c1.changeValue(6);
  assert(c1.getValue()==6);
  assert(!c1.isSB());
  c3.changeValue(11);
  assert(c3.getValue()==11);
  assert(c3.isSB());
  c5.changeValue(7);
  assert(c5.getValue()==7);
  assert(!c5.isSB());

  //test operator overloading
  assert(c2==c5);
  assert(!(c2==c3));
  assert(!(c4==c6));

}
  
  static void pileClassTest(){
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
    Card c10(10);
    Card c11(11);
    Card c12(12);

    Pile *pptr = new Pile();
    Pile &p = *pptr; 
    vector<Card> v = {c0, c1, c2, c3, c4, c5 ,c6, c7, c8, c9, c10, c11, c12};
    p.cards.insert(p.cards.begin(),v.begin(),v.end());

    //test getSize() and flipTop()
    assert(p.getSize()==13);
    assert(p.flipTop()==0); 
    
    //test getCard() which deletes card c0 and now c1 is the top card
    assert(p.getCard()== c0);
    assert(p.getSize()==12);
    assert(p.flipTop()==1);

    assert(p.getCard()== c1);
    assert(p.getSize()==11);
    assert(p.getCard()== c2);
    assert(p.getSize()==10);
    assert(p.flipTop()==3);

    delete pptr; 

    Pile *ppptr = new Pile();
    Pile &pp = *ppptr;
    vector<Card> v2 = {c3, c5, c7, c0, c1};
    pp.cards.insert(pp.cards.begin(),v2.begin(),v2.end());
    assert(pp.getSize()==5);
    assert(pp.flipTop()== 3);
    assert(pp.getCard()== c3);
    assert(pp.getSize()==4);
    assert(pp.flipTop()==5);
    assert(pp.getCard()== c5);
    assert(pp.getSize()==3);
    assert(pp.flipTop()==7);

    delete ppptr; 
  }

  static void buildingPileTest() {
    Card c1(1);
    Card c2(2);
    Card c3(3);
    Card c4(4);
    Card c5(5);
    Card c6(6);
    Card c7(7);
    Card c8(8);
    Card c9(9);
    Card c10(10);
    Card c11(11);
    Card c12(12);
    buildingPile * bp1ptr = new buildingPile(); //checks if constructor works
    buildingPile &bp1 = *bp1ptr;
    vector<Card> v = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
    bp1.cards.insert(bp1.cards.begin(),v.begin(),v.end());
    assert(bp1.getSize() == 12); // checks all cards were added

    //test emptyPile()
    bp1.emptyPile(); //empty building pile
    assert(bp1.cards.empty()); // check that all cards were erased

    bp1.cards.push_back(c3); // adds one 1 more card to vector
    assert(!bp1.cards.empty()); //checks if vector is not empty
    bp1.emptyPile(); //empties building pile
    assert(bp1.cards.empty()); //checks that all cards were erased

    delete bp1ptr;
  }

  static void drawDeckTest() {
    Card c1(1);
    Card c2(2);
    Card c3(3);
    Card c4(4);
    Card c5(5);
    Card c6(6);
    Card c7(7);
    Card c8(8);
    Card c9(9);
    Card c10(10);
    Card c11(11);
    Card c12(12);
    drawDeck *d1ptr = new drawDeck();
    drawDeck & d1 = *d1ptr;
    vector<Card> v = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
    d1.cards.insert(d1.cards.begin(),v.begin(),v.end());;
    assert(d1.getSize() == 12); // checks size of drawDeck
    assert(d1.getSize() != 5);
    assert(d1.flipTop() == 1);

    //tests shuffle()
    bool different;
    do {
      d1.shuffle(); // shuffles cards in vector
      assert(d1.getSize() == 12);
      if (d1.cards.at(0) == c1 && d1.cards.at(1) == c2 && d1.cards.at(2) == c3 && d1.cards.at(3) == c4 && d1.cards.at(4) == c5 && d1.cards.at(5) == c6 && d1.cards.at(6) == c7 && d1.cards.at(7) == c8 && d1.cards.at(8) == c9 && d1.cards.at(9) == c10 && d1.cards.at(10) == c11 && d1.cards.at(11) == c12) {
	different = false;
      } else {
	different = true;
      }
    } while (different == false) ;
    assert(different == true); // checks cards are not in the same order

    delete d1ptr; 

    drawDeck *d2ptr= new drawDeck();
    drawDeck &d2 = *d2ptr;
    vector<Card> v2 = {c1, c2, c3};
    d2.cards.insert(d2.cards.begin(),v2.begin(),v2.end());
    assert(d2.getSize() == 3); //checks getSize function
    assert(d2.getSize() != 12);
    assert(d2.flipTop() == 1);
    assert(d2.flipTop() != 3);

    do {
      d2.shuffle(); // shuffles cards in vector
      assert(d2.getSize() == 3); // checks all cards in vector
      if (d2.cards.at(0) == c1 && d2.cards.at(1) == c2 && d2.cards.at(2) == c3) {
	different = false;
      } else {
	different = true;
      }
    } while (different == false) ;
    assert(different == true); // checks cards are not in the same order

    delete d2ptr; 
  }



  static void handTest(){
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
    Card c10(10);
    Card c11(11);
    Card c12(12);

    drawDeck *dptr = new drawDeck();
    drawDeck &d = *dptr;
    vector<Card> v = {c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
    d.cards.insert(d.cards.begin(),v.begin(),v.end());
    assert(d.getSize() == 13);
    Hand *hptr = new Hand(3);
    Hand &h = *hptr;
    vector<Card> v2 = {c3, c7, c1};
    h.cards.insert(h.cards.begin(),v2.begin(),v2.end());
    //tests update() - adds two cards into the hand since Hand always needs 5 cards
    h.update(d);
    assert (h.cards.at(0)==c3);
    assert (h.cards.at(1)==c7);
    assert (h.cards.at(2)==c1);
    assert (h.cards.at(3)==c0);
    assert (h.cards.at(4)==c1);
    assert (h.getSize()==5); 

    assert(d.getSize()==11);
    assert(d.cards.at(0)== c2);

    delete hptr; 
    
    //testing default constructor 
    Hand *hhptr = new Hand();
    Hand &hh = *hhptr;
    hh.update(d); 
    assert (hh.cards.at(0)==c2);
    assert (hh.cards.at(1)==c3);
    assert (hh.cards.at(2)==c4);
    assert (hh.cards.at(3)==c5);
    assert (hh.cards.at(4)==c6);
    assert (hh.getSize()==5); 
    
    assert(d.getSize()==6);
    assert(d.cards.at(0)== c7);
    
    delete hhptr; 
    delete dptr; 
  }

  static void stockTest() {
    Stock *s1ptr = new Stock();
    Stock &s1 = *s1ptr; 
    assert(s1.getSize() == 0);
    assert(s1.win());

    delete s1ptr;

    Card c1(1);
    Card c2(2);
    Card c3(3);
    Card c4(4);
    Card c5(5);
    Card c6(6);
    Card c7(7);
    Card c8(8);
    Card c9(9);
    Card c10(10);
    Card c11(11);
    Card c12(12);

    Stock *s2ptr = new Stock();
    Stock &s2 = *s2ptr;
    vector<Card> v = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12};
    s2.cards.insert(s2.cards.begin(),v.begin(),v.end());
    assert(s2.getSize() == 12);

    //tests win()
    assert(!s2.win());
    s2.cards.erase(s2.cards.begin(), s2.cards.end());
    assert(s2.cards.empty());
    assert(s2.getSize() == 0);
    assert(s2.win());

    s2.cards.push_back(c10);
    assert(s2.flipTop() == 10);
    assert(s2.getSize() == 1);
    assert(!s2.win());
    delete s2ptr; 

  }


 
};

int main(void){
  cout << "Running Pile tests..." << endl;
  pileTest::cardTest();
  pileTest::pileClassTest();
  pileTest::buildingPileTest();
  pileTest::drawDeckTest();
  pileTest::handTest();
  pileTest::stockTest();
  cout << "Pile tests passed." << endl; 
}
