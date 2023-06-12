#include <stdio.h>
#include <stdlib.h>
#include "../include/deck.hpp"

Deck::Deck() 
{
  int index = 0;
  for (int suit = 0; suit < 4; suit++) {
    for (int number = 2; number < 15; number++) {
      cards[index].Initialize(suit, number);
      index++;
    }
  }
}


void Deck::Print() const
{
  for (int i = 0; i < kDeckSize; i++)
    cards[i].Print();
} 


void Deck::Shuffle() {
  for (int c = 0; c < 1000; c++) {
    int card1 = arc4random_uniform(52);
    int card2 = arc4random_uniform(52);
    Card temp;
    temp = cards[card1];
    cards[card1] = cards[card2];
    cards[card2] = temp;
  }
} 


bool Deck::HasDuplicates() const {
  for (int i = 0; i < kDeckSize; i++) {
    const Card &card1 = cards[i];
    for (int j = i + 1; j < kDeckSize; j++) {
      const Card &card2 = cards[j];
      if ( card1 == card2)
        return 1;
    }
  }
  return 0;
} 

