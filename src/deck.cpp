#include <stdio.h>
#include <stdlib.h>
#include "deck.hpp"

//Deck::Deck()
//{
//}

void Deck::Fill() 
{
    int index = 0;
    for (int suit = 0; suit < 4; suit++) {
        for (int number = 2; number < 15; number++) {
            cards[index] = Card(suit, number);
            length++;
            index++;
        }
    }
}

void Deck::Print() const
{
    for (int i = 0; i < kDeckSize; i++)
        if ((cards[i] == NULLCARD) != true)
            cards[i].Print();
} 


void Deck::Shuffle() {
    for (int c = 0; c < 1000; c++) {
        int card1 = arc4random_uniform(length);
        int card2 = arc4random_uniform(length);
        if ((cards[card1] == NULLCARD || cards[card2] == NULLCARD) != true)
        {
            Card temp;
            temp = cards[card1];
            cards[card1] = cards[card2];
            cards[card2] = temp;
        }
    }
} 


bool Deck::HasDuplicates() const {
    for (int i = 0; i < kDeckSize; i++) {
        const Card &card1 = cards[i];
        
        // null cards can't be a duplicate of anything else, especially other nullcards
        if( card1 == NULLCARD)
            continue;
        
        for (int j = i + 1; j < kDeckSize; j++) {
            const Card &card2 = cards[j];
            if ( card1 == card2 )
                return 1;
        }
    }
    
    return 0;
} 

