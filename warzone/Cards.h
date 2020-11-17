#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Orders.h"
#include "Player.h"

class Order;
class Player;

using namespace std;

// Card Objects
class Card
{
protected:
	string name;
public:
	Card();
	Card(Card* card);
	~Card();
	Card* operator= (const Card& card);

	virtual Order* play(Player* owner);
	string getName();
	friend ostream& operator<< (ostream& out, const Card& card);
};

class SpyCard : public Card {
public:
	SpyCard();
	SpyCard(SpyCard* spycard);
	~SpyCard();
	SpyCard* operator= (const SpyCard& card);

	Order* play(Player* owner);
};

class BombCard :public Card {
public:
	BombCard();
	BombCard(BombCard* bombCard);
	~BombCard();
	BombCard* operator= (const BombCard& card);

	Order* play(Player* owner);
};

class ReinforcementCard :public Card {
public:
	ReinforcementCard();
	ReinforcementCard(ReinforcementCard* rCard);
	~ReinforcementCard();
	ReinforcementCard* operator= (const ReinforcementCard& card);

	Order* play(Player* owner);
};

class BlockadeCard :public Card {
public:
	BlockadeCard();
	BlockadeCard(BlockadeCard* bCard);
	~BlockadeCard();
	BlockadeCard* operator= (const BlockadeCard& card);

	Order* play(Player* owner);
};

class AirliftCard :public Card {
public:
	AirliftCard();
	AirliftCard(AirliftCard* aCard);
	~AirliftCard();
	AirliftCard* operator= (const AirliftCard& card);

	Order* play(Player* owner);
};

class DiplomacyCard :public Card {
public:
	DiplomacyCard();
	DiplomacyCard(DiplomacyCard* dCard);
	~DiplomacyCard();
	DiplomacyCard* operator= (const DiplomacyCard& card);

	Order* play(Player* owner);
};

class Deck {
private:
	std::vector<Card*>* fullDeck;
public:
	Deck();
	Deck(Deck* Deck);
	~Deck();
	Deck* operator= (const Deck& deck);

	const std::vector<Card*>* getDeck();
	void add(Card* card);

	Card* draw();

	friend ostream& operator<< (ostream& out, const Deck& deck);
};

// Handy
class Hand {
private:
	Deck* deck;
	Player* owner;
	vector<Card*>* currentHand;

public:
	Hand(Deck* deck);
	Hand(Deck* deck, Player* player);
	Hand(Hand* hand);
	~Hand();
	Hand* operator= (const Hand& hand);

	void addCard(Card* card);
	void play(int index);

	const vector<Card*>* getCurrentHand();

	friend ostream& operator<< (ostream& out, const Hand& hand);
};