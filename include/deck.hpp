/*
example include file
*/

#include "../include/card.hpp"

#ifdef __cplusplus

class Deck
{
    private:
      static constexpr int kDeckSize = 52;
      Card cards[kDeckSize];

    public:
      Deck();

      const Card & operator[]( int index ) const { assert(index >= 0 && index < kDeckSize); return cards[index];}

      /*! Print the deck to standard out */
      void Print() const;

      /*! Randomly resort the deck */
      void Shuffle();

      /*! returns true if the deck has multiple copies of the same card */
      bool HasDuplicates() const;

      /*! return the number */
      constexpr inline int GetDeckSize() const {return (sizeof(cards)/sizeof(Card));}

};

extern "C" {
#endif /* __cplusplus */

void printHello(void);
void tester();

#ifdef __cplusplus
}
#endif /* __cplusplus */
