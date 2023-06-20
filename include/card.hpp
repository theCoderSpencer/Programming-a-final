/*
example include file
*/

#ifdef __cplusplus 
#include <iostream>
#include <stdexcept>
#define NULLCARD Card::NullCard
#define UNUSED __attribute__ ((__unused__))


typedef enum : uint8_t
{
    kCardPropertyNone   = 0,
    kCardPropertyStolen,
}CardProperty;

class Card
{
    friend class Deck;


  public:
    static const Card NullCard;
    
    uint8_t number,suit;
    CardProperty property;
    
    Card() : Card(0,0){}
    Card(int _suit, int _number) : property(kCardPropertyNone) {suit = _suit; number = _number;}
    
    const char * GetName() const;
    const char * GetSuit() const;

    void Print() const;

    // Formerly CardMatchCheck
    // CAUTION NULLCARD == NULLCARD is true
    inline bool operator==(const Card & card2) const{ return number == card2.number && suit == card2.suit; }
    
};

extern "C" {
#endif /* __cplusplus */

void printHello(void);
void tester();

#ifdef __cplusplus
}
#endif /* __cplusplus */
