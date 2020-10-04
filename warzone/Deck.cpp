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

		void Deck::printDeck()
		{
			cout << "Here are the contents of the deck"<< endl;
			int i = 1;
			for (std::vector<Card*>::iterator it = fullDeck->begin(); it != fullDeck->end(); ++it) {

				cout << i++ << ' ' << (*it)->getName() << endl;
			}
		}
		void Deck::printDrawpile()
		{
			cout << "Here are the contents of the drawpile" << endl;
			int i = 1;
			for (std::vector<int*>::iterator it = drawPile->begin(); it != drawPile->end(); ++it) {

				int* cardID = (*it);
				cout << i++ << ' ' << (int) cardID<< endl;
			}
		}
		void Deck::printFromCatalog(int cardID)
		{
			cout<< this->fullDeck->operator[]((size_t)cardID )->getName() << endl;
		}
}
