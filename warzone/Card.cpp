#include "Card.h"

namespace Cards {

	Card::Card() {
		this->name = new string("Basic Card");
	}

	Card::~Card()
	{
		delete name;
	}
	
	void Card::play()
	{
		cout << "this is a basic Card";
	}




	SpyCard::SpyCard()
	{
		this->name= new std:: string("Spy Card");
	}

	SpyCard::~SpyCard()
	{
	}

	void SpyCard::play()
	{
		cout << "I am a SpyCard";
	}

	BombCard::BombCard()
	{
		this->name = new std::string("BombCard");
	}

	BombCard::~BombCard()
	{
	}

	void BombCard::play()
	{
		cout << "I am a BombCard";
	}

	ReinforcementCard::ReinforcementCard()
	{
		name = new std::string("ReinforcementCard");
	}

	ReinforcementCard::~ReinforcementCard()
	{
	}

	void ReinforcementCard::play()
	{
		cout << "I am a ReinforcementCard";
	}

	BlockadeCard::BlockadeCard()
	{
		name = new std::string("BlockadeCard");
	}

	BlockadeCard::~BlockadeCard()
	{
	}

	void BlockadeCard::play()
	{
		cout << "I am a BlockadeCard";
	}
		
	AirliftCard::AirliftCard()
	{
		name = new std::string("AirliftCard");
	}

	AirliftCard::~AirliftCard()
	{
		
	}

	void AirliftCard::play()
	{
		cout << "I am a AirliftCard";
	}

	DiplomacyCard::DiplomacyCard()
	{
		name = new std::string("DiplomacyCard");
	}

	DiplomacyCard::~DiplomacyCard()
	{
		
	}

	void DiplomacyCard::play()
	{
		cout << "I am a DiplomacyCard";
	}
}
