#include "Cards.h"

namespace Cards {

	// Card functions
	Card::Card() {
		this->name = new string("Basic Card");
	}

	Card::Card(Card* card)
	{
		this->name = &card->getName();
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
		out << name;
		return out;
	}

	Card& Card::operator=(const Card& card)
	{
		return new Card(card);
	}

	// Spy Cards
	SpyCard::SpyCard() : Card()
	{
		this->name = new std::string("Spy Card");
	}

	SpyCard::SpyCard(SpyCard* spycard) : Card(spycard)
	{
	}

	SpyCard::~SpyCard()
	{
	}

	SpyCard& SpyCard::operator=(const SpyCard& card)
	{
		return new SpyCard(card);
	}

	void SpyCard::play()
	{
		cout << "Playing SpyCard" << endl;
	}

	// Bomb Cards
	BombCard::BombCard(): Card()
	{
		this->name = new std::string("BombCard");
	}

	BombCard::BombCard(BombCard* bombCard) : Card(bombCard)
	{
	}

	BombCard::~BombCard()
	{
	}

	BombCard& BombCard::operator=(const BombCard& card)
	{
		return new BombCard(card);
	}

	void BombCard::play()
	{
		cout << "Playing BombCard" << endl;
	}

	// Reinforcement Cards
	ReinforcementCard::ReinforcementCard() : Card()
	{
		name = new std::string("ReinforcementCard");
	}

	ReinforcementCard::ReinforcementCard(ReinforcementCard* rCard) : Card(rCard)
	{
	}

	ReinforcementCard::~ReinforcementCard()
	{
	}

	ReinforcementCard& ReinforcementCard::operator=(const ReinforcementCard& card)
	{
		return new ReinforcementCard(card);
	}

	void ReinforcementCard::play()
	{
		cout << "Playing ReinforcementCard" << endl;
	}

	// Blockade Cards
	BlockadeCard::BlockadeCard(): Card()
	{
		name = new std::string("BlockadeCard");
	}

	
	BlockadeCard::BlockadeCard(BlockadeCard* bCard) : Card(bCard)
	{
	}

	BlockadeCard& BlockadeCard::operator=(const BlockadeCard& card)
	{
		return new BlockadeCard(card);
	}

	BlockadeCard::~BlockadeCard()
	{

	}

	void BlockadeCard::play()
	{
		cout << "Playing BlockadeCard" << endl;
	}

	// Airlift Cards
	AirliftCard::AirliftCard() : Card()
	{
		name = new std::string("AirliftCard");
	}

	AirliftCard::AirliftCard(AirliftCard* aCard) : Card(aCard)
	{
	}

	AirliftCard::~AirliftCard()
	{

	}

	AirliftCard& AirliftCard::operator=(const AirliftCard& card)
	{
		return new AirliftCard(card);
	}

	void AirliftCard::play()
	{
		cout << "Playing AirliftCard" << endl;
	}

	// Diplomacy Cards
	DiplomacyCard::DiplomacyCard() : Card()
	{
		name = new std::string("DiplomacyCard");
	}

	DiplomacyCard::DiplomacyCard(DiplomacyCard* dCard) : Card(dCard)
	{
	}

	DiplomacyCard::~DiplomacyCard()
	{

	}

	DiplomacyCard& DiplomacyCard::operator=(const DiplomacyCard& card)
	{
		return new DiplomacyCard(card);
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

	Deck::Deck(Deck* deck)
	{
		this->fullDeck = new vector<Card*>;
		this->drawPile = new vector<int*>;

		for (int i = 0; i < deck->fullDeck->size(); i++)
		{
			fullDeck->push_back(deck->fullDeck->at(i));
		}
		for (int i = 0; i < deck->drawPile->size(); i++)
		{
			drawPile->push_back(deck->drawPile->at(i));
		}
	}

	Deck::~Deck()
	{
		fullDeck->clear();
		delete fullDeck;
		drawPile->clear();
		delete drawPile;
	}

	Deck& Deck::operator=(const Deck& deck)
	{
		return new Deck(deck);
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

			out << *(*it) << "\t\tID: " << i++ << endl;
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

	Hand::Hand(Hand* hand)
	{
		this->deck = new Deck(hand->deck);
		this->currentHand = new vector<int*>;

		for (int i = 0; i < hand->currentHand->size(); i++)
		{
			currentHand->push_back(hand->currentHand->at(i));
		}
	}

	Hand::~Hand()
	{
		delete deck;
		currentHand->clear();
		delete  currentHand;
	}

	Hand& Hand::operator=(const Hand& hand)
	{
		return new Hand(hand);
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
	vector<int*>* Hand::getCurrentHand()
	{
		return this->currentHand;
	}
	ostream& operator<<(ostream& out, const Hand& hand)
	{
		out << "This is my current hand" << endl;

		for (int i = 0; i < hand.currentHand->size(); i++)
		{
			int* cardID = hand.currentHand->operator[](i);
			Card* card = hand.deck->getFromCatalog(cardID);

			out << "ID: " <<(int)cardID << ' ' << *card<< endl;
		}
		out << "---------" << endl;

		return out;

	}
}
