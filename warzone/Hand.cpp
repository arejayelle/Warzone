#pragma once
#include "Hand.h"

namespace Cards {

	Hand::Hand(Deck* deck) {
		this->deck = deck;
		this->currentHand = new vector<int*>;
	}

	void Hand::addCard(int* cardId)
	{
		currentHand->push_back(cardId);
	}

	void Hand::play(int index) {
	}

}