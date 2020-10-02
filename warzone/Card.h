#pragma once
#include <iostream>
using namespace std;

class Card
{
public: 
	virtual void play() = 0; 
};

class SpyCard: Card {
	void play();
};

class BombCard: Card {
	void play();
};

class ReinforcementCard: Card {
	void play();
};

class BlockadeCard: Card {
	void play();
};

class AirliftCard: Card {
	void play();
};


class DiplomacyCard: Card {
	void play();
};

