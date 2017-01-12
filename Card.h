#ifndef _CARD_H
#define _CARD_H

class Card
{
  friend class pileTest; 
  friend class playersTest; 
  friend class gameTest; 
 private:
  int value;
  bool isSkipBo; 
 public:
  Card(int val);
  int getValue();
  bool operator==(const Card &rhs) const; //equal operator
  bool isSB(); 
  void changeValue(int newValue); 
};

#endif
