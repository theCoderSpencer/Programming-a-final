/*
example include file
*/

#ifdef __cplusplus 
#include <iostream>
#include <stdexcept>

class Card
{
  protected:
    friend class Deck;
    Card(){}

  public:
    int number,suit;
    Card(int _suit, int _number) {Initialize(_suit, _number); }
    Card( const Card & card){number = card.number; suit = card.suit;}
    inline Card & Initialize(int _suit, int _number){ suit = _suit; number = _number; return *this;}

    const char * GetName() const;
    const char * GetSuit() const;

    void Print() const;

    // Formerly CardMatchCheck
    inline bool operator==(const Card & card2) const{ return number == card2.number && 
                                                             suit   == card2.suit; }
};

extern "C" {
#endif /* __cplusplus */

void printHello(void);
void tester();

#ifdef __cplusplus
}
#endif /* __cplusplus */
