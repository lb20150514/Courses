#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;

void shuffle(int cut, Deck &deck, Player *player)
//MODIFIED: cut > 0
//EFFECTS: shuffle and let player know that, announce the shuffle
{
    deck.shuffle(cut);
    player->shuffled();
    cout << "cut at " << cut << endl;
}

void dealPlayer(const Card card, Player *player, Hand &hand)
//EFFECTS: expose the card to the player, add the card to player's hand,
//      announce the card.
{
    player->expose(card);
    hand.addCard(card);
    cout << "Player dealt " << SpotNames[card.spot] << " of " << SuitNames[card.suit] << endl;
}

void dealDealer(const Card card, Player *player, Hand &hand)
//EFFECTS: expose the card to the player, add the card to dealer's hand,
//      announce the card.
{
    player->expose(card);
    hand.addCard(card);
    cout << "Dealer dealt " << SpotNames[card.spot] << " of " << SuitNames[card.suit] << endl;
}

int main(int argc, char* argv[])
{
    //initialize data
    int bankroll = atoi(argv[1]), min_bet = atoi(argv[2]), hands = atoi(argv[3]), thishand = 1, cut = 0;
    unsigned int wager;
    string filename = "", scut = "";
    Deck deck;
    Player *player = NULL;
    Hand playerhand, dealerhand;

    if ((string) argv[4] == "simple")
        player = get_Simple();
    else if ((string) argv[4] == "counting")
        player = get_Counting();

    //initially shuffle
    cout << "# Shuffling the deck\n";
    if (argc >= 6)
    {
        ifstream iFile;
        filename = argv[5];
        iFile.open(filename);
        getline(iFile, scut);
        istringstream istring;
        istring.str(scut);
        while (!istring.eof())
        {
            istring >> cut;
            shuffle(cut, deck, player);
        }
    }
    else
    {
        for (int i = 0; i < 7; i ++)
            shuffle(get_cut(), deck, player);
    }

    if (bankroll < min_bet)
    {
        cout << "# Player has " << bankroll << " after 0 hands\n";
        return 0;
    }

    //simulate hands
    while (thishand <= hands)
    {
        playerhand.discardAll();
        dealerhand.discardAll();
        Card dealerTemp, holeCard;

        //check bankroll
        if (bankroll < min_bet)
        {
            cout << "# Player has " << bankroll << " after " << thishand << " hands\n";
            break;
        }

        //announce the hand
        cout << "# Hand " << thishand << " bankroll " << bankroll << endl;
        thishand ++;

        //reshuffle
        if (deck.cardsLeft() < 20)
        {
            cout << "# Shuffling the deck\n";
            for (int i = 0; i < 7; i ++)
                shuffle(get_cut(), deck, player);
        }
        //ask for a wager
        wager = player->bet(bankroll, min_bet);
        cout << "# Player bets " << wager << endl;

        //deal four cards
        dealPlayer(deck.deal(), player, playerhand);//player face-up 1
        dealerTemp = deck.deal();
        dealDealer(dealerTemp, player, dealerhand);//dealer face-up
        dealPlayer(deck.deal(), player, playerhand);//player face-up 2
        holeCard = deck.deal();//dealer face-down

        //if natural 21
        if (playerhand.handValue().count == 21)
        {
            cout << "# Player dealt natural 21\n";
            bankroll += wager * 3 / 2;
            continue;
        }
            //if not natural 21
        else
        {
            //player
            while (player->draw(dealerTemp, playerhand))
                dealPlayer(deck.deal(), player, playerhand);
            cout << "Player's total is " << playerhand.handValue().count << endl;

            //if player bust
            if (playerhand.handValue().count > 21)
            {
                bankroll -= wager;
                cout << "# Player busts\n";
                continue;
            }
            else
            //dealer
            {
                //expose hole card
                player->expose(holeCard);
                dealerhand.addCard(holeCard);
                cout << "Dealer's hole card is " << SpotNames[holeCard.spot] << " of " << SuitNames[holeCard.suit] << endl;

                while (dealerhand.handValue().count < 17)
                    dealDealer(deck.deal(), player, dealerhand);
                cout << "Dealer's total is " << dealerhand.handValue().count << endl;

                //announce result for this hand

                if (dealerhand.handValue().count > 21)
                {
                    bankroll += wager;
                    cout << "# Dealer busts\n";
                }
                else if (dealerhand.handValue().count > playerhand.handValue().count)
                {
                    bankroll -= wager;
                    cout << "# Dealer wins\n";
                }
                else if (dealerhand.handValue().count < playerhand.handValue().count)
                {
                    bankroll += wager;
                    cout << "# Player wins\n";
                }
                else if (dealerhand.handValue().count == (playerhand.handValue()).count)
                    cout << "# Push\n";
            }
        }
        
        if (thishand > hands)
            cout << "# Player has " << bankroll << " after " << hands << " hands\n";
    }
    return 0;
}
