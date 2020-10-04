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

		void add(Card* card);
		Card* getFromCatalog(int* cardID);

		int* draw();
		void returnToDrawPile(int* index);

		void printDeck();
		void printDrawpile();
		void printFromCatalog(int cardID);
	};

}
