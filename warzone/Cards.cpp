#include "Cards.h"

namespace Cards {

	// Card functions
	Card::Card() {
		this->name = new string("Basic Card");
	}

	Card::~Card()
	{
		delete name;
	}

	void Card::play()
	{
		cout << "this is a basic Card" << endl;
	}

	string Card::getName()
	{
		return *name;
	}

	ostream& operator<<(ostream& out, const Card& card)
	{
		string name = (string) *card.name;
		out << name<< endl;
		return out;
	}

	// Spy Cards
	SpyCard::SpyCard()
	{
		this->name = new std::string("Spy Card");
	}

	SpyCard::~SpyCard()
	{
	}

	void SpyCard::play()
	{
		cout << "Playing SpyCard" << endl;
	}

	// Bomb Cards
	BombCard::BombCard()
	{
		this->name = new std::string("BombCard");
	}

	BombCard::~BombCard()
	{
	}

	void BombCard::play()
	{
		cout << "Playing BombCard" << endl;
	}

	// Reinforcement Cards
	ReinforcementCard::ReinforcementCard()
	{
		name = new std::string("ReinforcementCard");
	}

	ReinforcementCard::~ReinforcementCard()
	{
	}

	void ReinforcementCard::play()
	{
		cout << "Playing ReinforcementCard" << endl;
	}

	// Blockade Cards
	BlockadeCard::BlockadeCard()
	{
		name = new std::string("BlockadeCard");
	}

	BlockadeCard::~BlockadeCard()
	{

	}

	void BlockadeCard::play()
	{
		cout << "Playing BlockadeCard" << endl;
	}

	// Airlift Cards
	AirliftCard::AirliftCard()
	{
		name = new std::string("AirliftCard");
	}

	AirliftCard::~AirliftCard()
	{

	}

	void AirliftCard::play()
	{
		cout << "Playing AirliftCard" << endl;
	}

	// Diplomacy Cards
	DiplomacyCard::DiplomacyCard()
	{
		name = new std::string("DiplomacyCard");
	}

	DiplomacyCard::~DiplomacyCard()
	{

	}

	void DiplomacyCard::play()
	{
		cout << "Playing DiplomacyCard" << endl;
	}

	// Deck functions
	Deck::Deck()
	{
		this->fullDeck = new std::vector<Card*>;
		this->drawPile = new std::vector<int*>;
		return;
	}

	Deck::~Deck()
	{
		fullDeck->clear();
		delete fullDeck;
		drawPile->clear();
		delete drawPile;
	}

	void Deck::add(Card* card)
	{
		fullDeck->push_back(card);
		int* size = (int*)fullDeck->size();
		drawPile->push_back(size);

	}

	Card* Deck::getFromCatalog(int* cardID)
	{
		if ((size_t)cardID < fullDeck->size())
		{
			return this->fullDeck->at((size_t)cardID);
		}
		return nullptr;
	}

	int* Deck::draw()
	{
		// randomly choose a value from the draw pile
		srand((unsigned int)time(NULL));
		int drawIndex = rand() % drawPile->size();

		// Retrieve cardID
		int* cardID = drawPile->operator[](drawIndex);

		// Get iterator at location for erasing
		std::vector<int*>::iterator it = drawPile->begin() + drawIndex;
		drawPile->erase(it);

		return cardID;
	}

	/*
	* Takes cardID and adds it to the bottom of the drawpile
	*/
	void Deck::returnToDrawPile(int* cardID)
	{
		drawPile->push_back(cardID);
	}

	ostream& operator<<(ostream& out, const Deck& deck)
	{
		out << "Here are the contents of the deck" << endl;

		int i = 0;
		for (std::vector<Card*>::iterator it = deck.fullDeck->begin(); it != deck.fullDeck->end(); ++it) {

			out << (*it) << "\t\tID: " << i++ << endl;
		}
		out << "----end of deck ----" << endl;

		return out;
	}
	
	void Deck::printDrawpile()
	{
		cout << "Here are the contents of the drawpile" << endl;
		cout << "index\tCard ID" << endl;

		int i = 0;
		for (std::vector<int*>::iterator it = drawPile->begin(); it != drawPile->end(); ++it) {

			int* cardID = (*it);
			cout << i++ << "\t" << (int)cardID << endl;
		}
	}

	// Hand functions
	Hand::Hand(Deck* deck)
	{
		this->deck = deck;
		this->currentHand = new vector<int*>;
	}

	Hand::~Hand()
	{
		delete deck;
		currentHand->clear();
		delete  currentHand;
	}

	void Hand::addCard(int* cardId)
	{
		currentHand->push_back(cardId);
	}

	void Hand::play(int index) 
	{
		if (index < currentHand->size()) {

			std::vector<int*>::iterator it = currentHand->begin() + index;
			Card* aCard = this->deck->getFromCatalog((*it));
			aCard->play();
			deck->returnToDrawPile(*it);
			currentHand->erase(it);
		}
	}

	void Hand::printHand()
	{
	}
	ostream& operator<<(ostream& out, const Hand& hand)
	{
		out << "This is my current hand" << endl;

		for (int i = 0; i < hand.currentHand->size(); i++)
		{
			int* cardID = hand.currentHand->operator[](i);
			Card* card = hand.deck->getFromCatalog(cardID);

			out << "ID: " <<(int)cardID << ' ' << card<< endl;
		}
		out << "---------" << endl;

		return out;

	}
}
