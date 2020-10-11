#pragma once
#include "Cards.h"
#include "Player.h"

namespace Cards {
	int main();

	void populateDeck(Deck* deck);
	void populateHand(Deck* deck, Hand* hand, int handSize);
	void playAllHand(Hand* hand, int handSize);
}
