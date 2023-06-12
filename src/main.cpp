#include "../include/deck.hpp"

int main() {
  
  Deck deck;
  deck.Print();
  deck.Shuffle();
  printf("\nshuffling...\n\n");
  deck.Print();
  
 
  return(0);
}