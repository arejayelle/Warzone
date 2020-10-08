#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

namespace Cards {

	// Card Objects
	class Card
	{
	protected:
		string* name;
	public:
		Card();
		Card(Card* card);
		~Card();
		virtual void play();
		string getName();
		friend ostream& operator<< (ostream& out, const Card& card);
	};

	class SpyCard : public Card {
	public:
		SpyCard();
		SpyCard(SpyCard* spycard);
		~SpyCard();

		void play();
	};

	class BombCard :public Card {
	public:
		BombCard();
		BombCard(BombCard* bombCard);
		~BombCard();
		void play();
	};

	class ReinforcementCard :public Card {
	public:
		ReinforcementCard();
		ReinforcementCard(ReinforcementCard* rCard);
		~ReinforcementCard();

		void play();
	};

	class BlockadeCard :public Card {
	public:
		BlockadeCard();
		BlockadeCard(BlockadeCard* bCard);
		~BlockadeCard();

		void play();
	};

	class AirliftCard :public Card {
	public:
		AirliftCard();
		AirliftCard(AirliftCard* aCard);
		~AirliftCard();

		void play();
	};

	class DiplomacyCard :public Card {
	public:
		DiplomacyCard();
		DiplomacyCard(DiplomacyCard* dCard);
		~DiplomacyCard();

		void play();
	};

	// Deck Object
	class Deck
	{
	private:
		std::vector<Card*>* fullDeck;
		std::vector <int*>* drawPile;

	public:
		Deck();
		Deck(Deck* deck);
		~Deck();

		void add(Card* card);
		Card* getFromCatalog(int* cardID);

		int* draw();
		void returnToDrawPile(int* index);

		friend ostream& operator<< (ostream& out, const Deck& deck);
		void printDrawpile();
	};

	// Hand 
	class Hand
	{
	private:
		Deck* deck;
		vector<int*>* currentHand;

	public:
		Hand(Deck* deck);
		Hand(Hand* hand);
		~Hand();

		void addCard(int* cardId);
		void play(int index);
		
		vector<int*>* getCurrentHand();
		
		friend ostream& operator<< (ostream& out, const Hand& hand);
	};
}
