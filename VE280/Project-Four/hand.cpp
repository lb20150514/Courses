#include "hand.h"

using namespace std;

Hand::Hand()
{
	discardAll();
}

void Hand::discardAll()
{
	curValue.count = 0;
	curValue.soft = false;
}

void Hand::addCard(Card c)
{
	switch (c.spot)
    {
       	case JACK: case QUEEN: case KING:
       		curValue.count += 10;
           	break;
       	case ACE:
       		curValue.count += 11;
           	curValue.soft = true;
           	break;
       	default:
        	curValue.count += (int) c.spot + 2;
            break;
    }
	if (curValue.count > 21 && curValue.soft)
	{
       	curValue.count -= 10;
       	curValue.soft = false;
    }
}

HandValue Hand::handValue() const
{
	return curValue;
}
