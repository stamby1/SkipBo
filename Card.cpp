#include "Card.h"

//constructor, sets the value of the card and whether it is a skipbo card.
Card::Card(int val){
  value = val;
  if(value == 0)
    isSkipBo = true;
  else
    isSkipBo = false;
}

//returns the value of the Card
int Card::getValue() {
  return value;
}

// == overload
bool Card:: operator==(const Card &rhs) const{
  if (value == (rhs.value)){
    return true; 
  }
  return false; 
}

//returns true if it is skipbo
bool Card::isSB(){
  return isSkipBo; 
}

//changes the value of skipbo card from 0 to desired number
//note that the isSkipBo boolean does  not change so we can keep track of whether or not the card was originally a SkipBo
void Card:: changeValue(int newValue){
  value = newValue; 
}
