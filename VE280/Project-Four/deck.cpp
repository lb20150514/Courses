#include "deck.h"

using namespace std;

Deck::Deck()
     : next(0)
{
    reset();
}

void Deck::reset()
{
    for (int i = 0; i < DeckSize; i++)
    {
        int iSpot = i % 13, iSuit = (i - iSpot) / 13;
        deck[i].suit = Suit(iSuit);
        deck[i].spot = Spot(iSpot);
    }
}

void Deck::shuffle(int n)
{
	int min = 0, nrest;
	(2 * n > DeckSize) ? (min = DeckSize - n) : (min = n);
  	if (min > 0)
  	{
  		Card tempDeck[DeckSize];
        for (int i = 0; i < DeckSize; i++)
        	tempDeck[i] = deck[i];
  	for (int i = 0; i < min; i ++)
  	{
    		deck[2 * i] = tempDeck[n + i];
    		deck[2 * i + 1] = tempDeck[i];
     	}
     	(min == n) ? (nrest = 2 * min) : (nrest = min);
	for (int i = 0; i < DeckSize - 2 * min; i ++)
		deck[2 * min + i] = tempDeck[nrest + i];
  	}
  	next = 0;
}

Card Deck::deal()
{
	if (next == DeckSize)
  	{
  		DeckEmpty empty;
  		throw empty;
  	}
  	next ++;
  	return deck[next - 1];
}

int Deck::cardsLeft()
{
	return DeckSize - next;
}
