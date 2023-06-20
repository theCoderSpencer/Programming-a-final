/*
 example include file
 */

#include "deck.hpp"

#ifdef __cplusplus
#define SIZEOFHAND (sizeof(Hand)/sizeof(Hand[0]))
class Player
{
public:
    int points;
    int handSize;
    Deck hand;
    
    Player() : points(0), handSize(0), hand(){};
    /*! Move a card from a deck to the player's hand*/
    void DrawCard(Deck & deck);
    void PrintHand();
};

extern "C" {
#endif /* __cplusplus */



#ifdef __cplusplus
}
#endif /* __cplusplus */

