#include "CardDriver.h"

namespace Cards {

	int main()
	{
		Deck* deck = new Deck();
		OrdersList* ordersList = new OrdersList();
		Player* player = new Player(nullptr, ordersList, deck);

		cout << "Creating Deck" << endl;
		cout << (*deck);

		cout << "Populating Deck" << endl;
		populateDeck(deck);
		cout << (*deck);

		cout << "Drawing 5 random cards" << endl;
		int handSize = 5;
		Hand* hand = new Hand(deck, player);

		populateHand(deck, hand, handSize);
		cout << *hand;

		cout << "CheckingDeck" << endl;
		cout << (*deck);

		cout << "\nPlaying all cards in hand" << endl;
		playAllHand(hand, handSize);

		cout << "CheckingDeck" << endl;
		cout << (*deck);

		return 0;
	}

	void populateDeck(Deck* deck)
	{
		SpyCard* spyCard = new SpyCard();
		BombCard* bombCard = new BombCard();
		ReinforcementCard* reinforcementCard = new ReinforcementCard();
		BlockadeCard* blockadeCard = new BlockadeCard();
		AirliftCard* airliftCard = new AirliftCard();
		DiplomacyCard* diplomacyCard = new DiplomacyCard();

		// add cards
		for (int i = 0; i < 4; i++) {
			deck->add(spyCard);
			deck->add(bombCard);
			deck->add(reinforcementCard);
			deck->add(airliftCard);
			deck->add(blockadeCard);
			deck->add(diplomacyCard);
		}

		return;
	}

	void populateHand(Deck* deck, Hand* hand, int handSize)
	{
		for (int i = 0;i < handSize;i++)
		{
			Card* card = deck->draw();
			hand->addCard(card);
		}
	}

	void playAllHand(Hand* hand, int handSize)
	{
		for (size_t i = 0; i < handSize; i++)
		{
			hand->play(0);
		}
		cout << "-------------- All cards played" << endl;
	}
}
