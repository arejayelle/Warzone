#include "Deck.h"

namespace Cards {

		Deck::Deck()
		{
			this->fullDeck = new std::vector<Card*>;
			this->drawPile = new std::vector<int*>;
			return;
		}

		Deck::~Deck()
		{
			fullDeck->clear();
			delete fullDeck;
			drawPile->clear();
			delete drawPile;
		}

}
