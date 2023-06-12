
#include "../include/card.hpp"


const char *Card::GetName() const {
  static const char *faces[13] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                                  "9", "10", "Jack", "Queen", "King", "Ace"};
  if (number < 2)
    return "<Error: card number too small>";
  if (number > 14)
    return "<Error: card number too big>";

  return faces[number - 2];
} 


const char *Card::GetSuit() const {
  static const char *suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

  if (suit < 0)
    return "<Suit too low>";
  if (suit > 3)
    return "<Suit too big>";
  return suits[suit];
} 


 void Card::Print() const {
  printf("%s of %s\n", GetName(), GetSuit());
} 

