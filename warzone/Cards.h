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
		~Card();
		virtual void play();
		string getName();
		friend ostream& operator<< (ostream& out, const Card& card);
	};

	class SpyCard : public Card {
	public:
		SpyCard();
		~SpyCard();

		void play();
	};

	class BombCard :public Card {
	public:
		BombCard();
		~BombCard();
		void play();
	};

	class ReinforcementCard :public Card {
	public:
		ReinforcementCard();
		~ReinforcementCard();

		void play();
	};

	class BlockadeCard :public Card {
	public:
		BlockadeCard();
		~BlockadeCard();

		void play();
	};

	class AirliftCard :public Card {
	public:
		AirliftCard();
		~AirliftCard();

		void play();
	};

	class DiplomacyCard :public Card {
	public:
		DiplomacyCard();
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
		~Hand();

		void addCard(int* cardId);
		void play(int index);
		
		vector<int*>* getCurrentHand();
		
		friend ostream& operator<< (ostream& out, const Hand& hand);
		void printHand();

	};
}
