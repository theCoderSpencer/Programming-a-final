#include "game.hpp"
#include <ctype.h>
using namespace std;

constexpr size_t kLineSize = 100;
ssize_t GetInput( char where[kLineSize] )\
{
    char * theLine = where;
    size_t lineSize = kLineSize;
    return getline(&theLine, &lineSize, stdin); //FIXME: 100+ characters in an input line crashes
}

static inline int CharToInteger( char c )
{
    assert( isdigit(c));    // make sure it is betwwen '0' and '9'
    return c - '0';
}

static inline int StringToInteger( const char * string, bool &success)
{
    char * endP = const_cast<char*>(string);
    long result = 0;
    
    if( NULL == string)
        goto fail;
    
    result = strtol( string, &endP, 10);
    if( endP == string)
        goto fail;

    success = true;
    return (int) result;
    
fail:
    success = false;
    return 0;
}

bool PlayArea::ChooseCardPlay() {
    char inputLine[kLineSize];
    int choice=0;
    cout << endl << "Enter 'x' to go back. Your Hand: " << endl;
    
    for (int i = 0; i< player.hand.length;i++)
        if (NULLCARD != player.hand[i])
            cout << i+1 << ". " << player.hand[i].GetName() << " of " << player.hand[i].GetSuit() << endl;
    
    cout << "Enter a number from 1 to " << player.hand.length << " to select a card" << endl;
    while (true) {
        GetInput(inputLine);
        choice = 0;
        if (inputLine[0] == 'x') {return false;}
        
        bool succeeded = false;
        choice = StringToInteger( inputLine, succeeded);
        if( ! succeeded )
        {
            cout << "Could not parse \"" << inputLine << "\"\n";
            continue;
        }
        
        if( choice <= 0 || choice > player.hand.length)
        {
            cout << "Choice too big/small for hand size. Try again.\n";
            continue;
        }
        
        if ((player.hand[choice-1].number+goalProgress > goal)) {
            if (14 != player.hand[choice-1].number) {
                cout << "This card cannot be played now; the sum of played card values would exceed the goal" << endl;
                break;
            }
            else {
                if ((goalProgress+1 <= goal) and (goalProgress+14 > goal)) {
                    player.hand[choice-1].number = 1;
                    cout << "Ace played for 1 point" << endl;
                }
            }
        }
            if (((choice > 0) and (choice <= player.hand.length)) and (player.hand[choice-1] != NULLCARD)) {
                PlayCard(player.hand[choice-1]);
                player.hand[choice-1] = player.hand[player.hand.length-1];
                player.hand[player.hand.length-1] = NULLCARD;
                player.hand.length--;
                lastPlayed = false;
                return true;
            }
        
            else
                cout << "Enter a valid number" << endl;
    }
    return false;
}

bool PlayArea::EndRound() {
    if (true == lastPlayed) {
        opponent.points += 1;
        cout << "Opponent wins a point (" << opponent.points << ")" << endl;
    }
    if (false == lastPlayed) {
        player.points += 1;
        cout << "You win a point (" << player.points << ")" << endl;
    }
    for (int i = 0; i <player.hand.length;i++) {
        if (kCardPropertyStolen == player.hand[i].property) {
            if (kCardPropertyStolen == player.hand[player.hand.length-1].property) {
                player.hand[player.hand.length-1] = NULLCARD;
                player.hand.length--;
                i--;
            }
            if (player.hand.length >= 2) {
                player.hand[i] = player.hand[player.hand.length-1];//FIXME: 1 stolen card in hand might be a problem
                player.hand[player.hand.length-1] = NULLCARD;
                player.hand.length--;
            }
        }
    }
    
    if (deck.length < 8) {
        if (player.points > opponent.points) {
            cout << "You win with " << player.points << " points" << endl;
            return false;
        }
        if (player.points < opponent.points) {
            cout << "Opponent wins with " << opponent.points << " points" << endl;
            return false;
        }
    }
    return true;
}

void PlayArea::StartTurn() {
    char inputLine[kLineSize];
    printf("\nYour Turn  enter 'h' for a list of commands\n");
    
    bool endTurn = false;
    while( endTurn == false )
    {
        GetInput(inputLine);
        switch (inputLine[0])
        {
            case 'h':
                printf("Commands:\n'h' help\n'space' pass\n'p' play card\n's' steal card from opponent\n'v' view cards in hand\n");
                break;
                
            case (char)32:
                cout << "Passing Turn.." << endl;
                passed = true;
                endTurn = true;
                break;
                
            case 'p':
                if (player.hand.length > 0) {
                    cout << "Play Card" << endl;
                    endTurn = ChooseCardPlay();
                    passed = false;
                }
                else {
                    cout << "You have no cards" << endl;
                    endTurn = false;
                }
                break;
                
            case 'v':
                cout << "Your cards: " << endl;
                for (int i = 0; i< player.hand.length;i++)
                    if (NULLCARD != player.hand[i])
                        cout << player.hand[i].GetName() << " of " << player.hand[i].GetSuit() << endl;
                break;
                
            case 's':
                if (opponent.hand.length > 0) {
                    cout << "Stealing Card.." << endl;
                    player.DrawCard(opponent.hand);
                    player.hand.cards[player.hand.length-1].property = kCardPropertyStolen;
                    cout << "Stolen Card: " << player.hand.cards[player.hand.length-1].GetName() << " of " << player.hand.cards[player.hand.length-1].GetSuit() << endl;
                    passed = false;
                    endTurn = true;
                }
                else {
                    cout << "Opponent has no cards" << endl;
                    endTurn = false;
                }
                break;
                
            default:
                printf("\nYour Turn  enter 'h' for a list of commands\n");
                break;
        }
        
    }
}

bool PlayArea::OpponentTurn() { 
    if (goalProgress == goal)
        return true;
    cout << "Opponent's Turn.." << endl;
    for (int i = 0; i < opponent.hand.length;i++) {
        if (((opponent.hand[i].number > 4)or(goal-goalProgress <= 4))and(opponent.hand[i] != NULLCARD)) {
            if (opponent.hand[i].number <= abs(goalProgress-goal) or (opponent.hand[i].number == 14)) { //opponent plays a card
                passed = false;
                if (opponent.hand[i].number == 14 and goalProgress+14 > goal)
                    opponent.hand[i].number = 1;
                PlayCard(opponent.hand[i]);
                opponent.hand[i] = opponent.hand[opponent.hand.length-1];
                opponent.hand[opponent.hand.length-1] = NULLCARD;
                opponent.hand.length--;
                lastPlayed = true;
                if (goalProgress == goal)
                    return true;
                else
                    return false;
            }
        }
    }
    if (player.hand.length > 1) { //opponent steals a card TODO: random drawing
        passed = false;
        opponent.DrawCard(player.hand);
        opponent.hand.cards[opponent.hand.length-1].property = kCardPropertyStolen;
        cout << "Stolen Card: " << opponent.hand.cards[opponent.hand.length-1].GetName() << " of " << opponent.hand.cards[opponent.hand.length-1].GetSuit() << endl;
    }
    else {
        cout << "Opponent Passes" << endl;
        if (true == passed)
            return true;
        passed = true;
    }
    
    if (goalProgress == goal)
        return true;
    else
        return false;
}

void PlayArea::StartRound() {

    goal = (16+arc4random_uniform(16+1))*playerCount;// use rand() for debuging
    goalProgress = 0;

    // Draw 4 cards
    constexpr int InitialHandSize = 4;
    
    for (int i = player.hand.length;i < InitialHandSize; i++)
        player.DrawCard(deck);

    printf("\n\nPlayer's hand:\n");
    player.PrintHand();

    for (int i = opponent.hand.length;i < InitialHandSize; i++)
        opponent.DrawCard(deck);
    
}

void PlayArea::StartGame() {
    // set up our deck
    deck.Fill();
    deck.Shuffle();
    playerCount = 2;
    
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
