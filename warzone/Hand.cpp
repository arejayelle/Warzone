#pragma once
#include "Hand.h"

namespace Cards {

	Hand::Hand(Deck* deck)
	{
		this->deck = deck;
		this->currentHand = new vector<int*>;
	}

	void Hand::addCard(int* cardId)
	{
		currentHand->push_back(cardId);
	}

	void Hand::play(int index) 
	{
		if (index < currentHand->size()) {

			std::vector<int*>::iterator it = currentHand->begin() + index;
			Card* aCard = this->deck->getFromCatalog((*it));
			aCard->play();
			deck->returnToDrawPile(*it);
			currentHand->erase(it);
		}
	}

	void Hand::printHand()
	{
		cout << "This is my current hand" << endl;

		for (int i = 0; i < currentHand->size(); i++)
		{
			int* cardID = currentHand->operator[](i);
			Card* card = this->deck->getFromCatalog(cardID);

			cout << "ID: " <<(int)cardID << ' ' << card->getName() << endl;
		}
		cout << "---------" << endl;
	}
}
