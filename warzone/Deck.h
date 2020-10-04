#pragma once

#include <vector>
#include "Card.h"

namespace Cards {

	class Deck
	{
	private:
		std::vector<Card*>* fullDeck;
		std::vector <int*>* drawPile;

	public:
		Deck();
		~Deck();
	};

}
