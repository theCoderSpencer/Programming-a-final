#include "player.hpp"


void Player::DrawCard(Deck & deck)
{
    /*for (int i = 0;i < deck.GetDeckSize();i++) {
        if( deck[i] != NULLCARD)
        {
            // Move the card from the deck to the hand
            hand[handSize++] = deck[i];
            
            // Remove the card from the deck
            deck[i] = NULLCARD;
            return;
        }
    }*/
    if (deck.length >= 1) {
        hand[hand.length++] = deck[deck.length-1];
        deck[deck.length-1] = NULLCARD;
        deck.length--;
    }
    else
        std::cout << "<Deck to draw from is too small>" << std::endl; //assert(deck.length >= 1);
    //printf("\n<Card Draw Error>\n");
}

void Player::PrintHand()
{
    hand.Print();
}



/*
 rules:
 make a random number from 16-32 and multiply it by number of players
 cards are valued at their number with these exeptions:
 jack = 11
 queen = 12
 king = 13
 ace = 1 or 14 (decide when card played)
 round starts:
 all players draw to a hand size of 4
 each player takes a turn
 on turn:
 pass (if all players pass on consecutive turns, the round ends), play a card, or steal a random card from an opponent's hand (if any player has no cards in hand, end round)
 if no player can play without the total value of played cards exeeding the random number, the round ends
 round ends:
 the last player to play a card wins a point
 all played or stolen cards are discarded
 the game ends when there are not enough cards for all players to have a hand of 4 cards
 when this occurs, the player with the most points wins!
 start a new round
 
 programming outline:
 make a deck class as a hand for the player and computer
 calculate a random value from 16-32 and multiply it by number of players
 draw card:
 if (deck size == 0): end game
 append copy of top card in deck to hand
 remove top card in deck
 round start:
 for each player: draw 4 cards into their hand
 players take turns
 on the player's turn:
 get input from the player
 use input to decide to either pass, steal a random card from opponent, or play a card from hand
 if (hand size of any hand == 0): end round
 if (total value == random number) player wins
 opponent's turn :
 for each card in hand:
 if (card's value == absolute value of total played card value - random number): play card and end turn
 compare values of cards in hand then if (any playable card that is above 4): play the highest value playable card
 else:
 if (player's card amount == 2):
 if (card in hand < distance from total to random number) play a playable card
 else: pass turn
 else: steal a card
 for each player: if (hand size == 0): end round
 round end:
 last player to play wins 1 point
 discard all stolen and played cards
 for each player: for each card in hand: {if (stolen == true): discard card} for (int i = 0;i >= absolute value of (hand size - 4);i++): draw a card
 
 
 
 */
