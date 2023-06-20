/*
example include file
*/

#include "card.hpp"

#ifdef __cplusplus

class Deck
{
  protected:
    friend class Player;
    friend class PlayArea;
    static constexpr int kDeckSize = 52;
    Card cards[kDeckSize];
    /*! Amount of non-null cards in deck*/
    int length;

  public:
    Deck() {length=0;};
    void Fill();

    Card & operator[]( int index ) { assert(index >= 0 && index < kDeckSize); return cards[index];} //FIXME: assert is sometimes triggered

    /*! Print the deck to standard out */
    void Print() const;

    /*! Randomly resort the deck */
    void Shuffle();

    /*! returns true if the deck has multiple copies of the same card */
    bool HasDuplicates() const;

    /*! return the number */
    constexpr inline int GetDeckSize() const {return kDeckSize;}

};

extern "C" {
#endif /* __cplusplus */

void printHello(void);
void tester();

#ifdef __cplusplus
}
#endif /* __cplusplus */
