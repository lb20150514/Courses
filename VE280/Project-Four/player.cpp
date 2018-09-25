#include "player.h"

using namespace std;

class PlayerSimple : public Player
{
public:
	int bet(unsigned int bankroll, unsigned int minimun);
  	bool draw(Card dealer, const Hand &player);
  	void expose(Card c);
	void shuffled();
};

class PlayerCounting : public Player
{
private:
	int count;
public:
	PlayerCounting();
	int bet(unsigned int bankroll, unsigned int minimun);
  	bool draw(Card dealer, const Hand &player);
  	void expose(Card c);
  	void shuffled();
};

PlayerCounting::PlayerCounting(): count(0)
{
}

int PlayerSimple::bet(unsigned int bankroll, unsigned int minimum)
{
  	return minimum;
}

int PlayerCounting::bet(unsigned int bankroll, unsigned int minimum)
{
    if (count >= 2 && bankroll >= 2 * minimum)
        return 2 * minimum;
    return minimum;
}

bool PlayerSimple::draw(Card dealer, const Hand &player)
{
   	HandValue value = player.handValue();
	if (!value.soft)
	{
  		if (value.count < 12) return true;
    		else if (value.count == 12)
     		{
     			switch (dealer.spot)
       	   		{
            			case FOUR: case FIVE: case SIX: return false;
        	    		default: return true;
            		}
    		}
        	else if (value.count < 17 && value.count > 12)
     		{
     			switch (dealer.spot)
       	   		{
            			case TWO: case THREE: case FOUR: case FIVE: case SIX: return false;
         	    		default: return true;
        		}
		}
	}
	else
	{
  		if (value.count < 18) return true;
     		else if (value.count == 18)
    		{
     			switch (dealer.spot)
       	   		{
            			case TWO: case SEVEN: case EIGHT: return false;
               			default: return true;
           		}
     		}
     		return false; 
  	}
}

bool PlayerCounting::draw(Card dealer, const Hand &player)
{
    PlayerSimple splayer;
    return splayer.draw(dealer, player);
}

void PlayerSimple::expose(Card c)
{
}

void PlayerCounting::expose(Card c)
{
	switch (c.spot)
  	{
  		case TEN: case JACK: case QUEEN: case KING: case ACE: 
			count --;
       	    		break;
    		case TWO: case THREE: case FOUR: case FIVE: case SIX:
       			count ++;
          		break;
        	default: break;
  	}
}

void PlayerSimple::shuffled()
{
}

void PlayerCounting::shuffled()
{
	count = 0;
}

Player *get_Simple()
{
	return new PlayerSimple();
}

Player *get_Counting()
{
	return new PlayerCounting();
}
