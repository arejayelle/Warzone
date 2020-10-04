#pragma once
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

namespace Cards {
	int main();

	void populateDeck(Deck* deck);
	void populateHand(Deck* deck, Hand* hand, int handSize);
	void playAllHand(Hand* hand, int handSize);
}
