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
			currentHand->erase(it);
		}
	}

}
