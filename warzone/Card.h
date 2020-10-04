#pragma once
#include <iostream>
using namespace std;

namespace Cards {

	class Card
	{
	protected:
		string* name;
	public: 
		Card();
		~Card();
		virtual void play(); 
	};

	class SpyCard: public Card {
	public: 
		SpyCard();
		~SpyCard();
	
		void play();
	};

	class BombCard:public Card {
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

}
