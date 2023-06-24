/*
 example include file
 */

#include "player.hpp"

#ifdef __cplusplus

class PlayArea {
    int goal,playerCount,goalProgress;
    bool lastPlayed,passed;
    Deck deck;
    Deck discard;
    Player player,opponent;
    
public:
    PlayArea() {goal=0;playerCount=2;goalProgress=0;lastPlayed = false;passed=false;}
    inline const int DeckLength() {return deck.length;}
    void StartGame();
    void StartRound();
    void StartTurn();
    bool ChooseCardPlay();
    bool OpponentTurn();
    bool EndRound();
    inline void PlayCard(Card& card) {assert(card.number+goalProgress <= goal); goalProgress += card.number; std::cout << card.GetName() << " of " << card.GetSuit() << " is played, increasing progress toward goal to " << goalProgress << "/" << goal << std::endl;}
};



extern "C" {
#endif /* __cplusplus */



#ifdef __cplusplus
}
#endif /* __cplusplus */
