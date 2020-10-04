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

		void Deck::add(Card* card)
		{
			fullDeck->push_back(card);
			int* size = (int*)fullDeck->size();
			drawPile->push_back(size);

		}

		Card* Deck::getFromCatalog(int* cardID)
		{
			if ((size_t)cardID < fullDeck->size())
			{
				return this->fullDeck->at((size_t)cardID);
			}
		}

		int* Deck::draw()
		{
			// randomly choose a value from the draw pile
			int drawIndex = rand() % drawPile->size();

			// Retrieve cardID
			int* cardID = drawPile->operator[](drawIndex);

			// Get iterator at location for erasing
			std::vector<int*>::iterator it = drawPile->begin() + drawIndex;
			drawPile->erase(it);

			return cardID;
		}

		/*
		* Takes cardID and adds it to the bottom of the drawpile
		*/
		void Deck::returnToDrawPile(int* cardID)
		{
			drawPile->push_back(cardID);
		}

}
