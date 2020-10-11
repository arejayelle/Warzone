#include "Cards.h"

namespace Cards {

	// Card functions
	
	/**
	 * Card Constructor
	 * 
	 */
	Card::Card() {
		this->name = new string("Basic Card");
	}

	/**
	 * Card Copy Constructor
	 * 
	 * \param card to be copied
	 */
	Card::Card(Card* card)
	{
		this->name = &card->getName();
	}

	/**
	 * Card Destructor
	 * 
	* Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 * 
	 */
	Card::~Card()
	{
		delete name;
	}

	/**
	 * Card Play function
	 * 
	 */
	void Card::play()
	{
		cout << "this is a basic Card" << endl;
	}

	/**
	 * \return name of this card
	 */
	string Card::getName()
	{
		return *name;
	}

	/**
	 * Stream insertion operator
	 * 
	 * \param out
	 * \param card
	 * \return 
	 */
	ostream& operator<<(ostream& out, const Card& card)
	{
		string name = (string) *card.name;
		out << name;
		return out;
	}

	/**
	 * Assignment operator
	 * 
	 * \param card
	 * \return 
	 */
	Card* Card::operator=(const Card& card)
	{
		return new Card(card);
	}

	// Spy Cards
	/**
	 * Spy Card default Constructor
	 * 
	 */
	SpyCard::SpyCard() : Card()
	{
		this->name = new std::string("Spy Card");
	}

	/**
	 * Spy Card Copy Constructor
	 * 
	 * \param spycard Card to be copied
	 */
	SpyCard::SpyCard(SpyCard* spycard) : Card(spycard)
	{
	}

	/**
	 * Spy Card Destructor
	 * 
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 * 
	 */
	SpyCard::~SpyCard()
	{
	}

	/**
	 * Assignment operator
	 * 
	 * \param card
	 * \return 
	 */
	SpyCard* SpyCard::operator=(const SpyCard& card)
	{
		return new SpyCard(card);
	}

	/**
	 * Play function
	 * 
	 */
	void SpyCard::play()
	{
		cout << "Playing SpyCard" << endl;
	}

	// Bomb Cards
	/**
	 * BombCard Default Constructor
	 * 
	 */
	BombCard::BombCard(): Card()
	{
		this->name = new std::string("BombCard");
	}

	/**
	 * BombCard Copy constructor
	 * 
	 * \param bombCard
	 */
	BombCard::BombCard(BombCard* bombCard) : Card(bombCard)
	{
	}

	/**
	 * BombCard Destructor
	 * 
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 * 
	 */
	BombCard::~BombCard()
	{
	}

	/**
	 * BombCard Assignment operator makes a copy of the passed Bomb card
	 * 
	 * \param card card to be copied
	 * \return 
	 */
	BombCard* BombCard::operator=(const BombCard& card)
	{
		return new BombCard(card);
	}

	/**
	 * Play function
	 *
	 */
	void BombCard::play()
	{
		cout << "Playing BombCard" << endl;
	}

	// Reinforcement Cards
	/**
	 * ReinforcementCard Default Constructor
	 * 
	 */
	ReinforcementCard::ReinforcementCard() : Card()
	{
		name = new std::string("ReinforcementCard");
	}

	/**
	 * ReinforcementCard Copy Constructor
	 * 
	 * \param rCard
	 */
	ReinforcementCard::ReinforcementCard(ReinforcementCard* rCard) : Card(rCard)
	{
	}

	/**
	 * ReinforcementCard destructor
	 * 
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 * 
	 */
	ReinforcementCard::~ReinforcementCard()
	{
	}

	/**
	 * Assignmenet operator makes copy of the passed card
	 */
	ReinforcementCard* ReinforcementCard::operator=(const ReinforcementCard& card)
	{
		return new ReinforcementCard(card);
	}

	/**
	 * Play function
	 *
	 */
	void ReinforcementCard::play()
	{
		cout << "Playing ReinforcementCard" << endl;
	}

	// Blockade Cards
	/**
	 * BlockadeCard Default Constructor
	 * 
	 */
	BlockadeCard::BlockadeCard(): Card()
	{
		name = new std::string("BlockadeCard");
	}

	/**
	 * BlockadeCard Copy Constructor
	 * 
	 * \param bCard
	 */
	BlockadeCard::BlockadeCard(BlockadeCard* bCard) : Card(bCard)
	{
	}

	/**
	 * Makes a copy of the passed card
	 * 
	 * \param card
	 * \return 
	 */
	BlockadeCard* BlockadeCard::operator=(const BlockadeCard& card)
	{
		return new BlockadeCard(card);
	}

	/**
	 * 
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 *  
	 */
	BlockadeCard::~BlockadeCard()
	{

	}

	/**
	 * Play function
	 *
	 */
	void BlockadeCard::play()
	{
		cout << "Playing BlockadeCard" << endl;
	}

	// Airlift Cards
	/**
	 * Default constructor
	 * 
	 */
	AirliftCard::AirliftCard() : Card()
	{
		name = new std::string("AirliftCard");
	}

	/**
	 * Copy Constructor.
	 * 
	 * \param aCard
	 */
	AirliftCard::AirliftCard(AirliftCard* aCard) : Card(aCard)
	{
	}

	/**
	 * 
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 *  
	 */
	AirliftCard::~AirliftCard()
	{

	}

	/**
	 * Makes a copy and assigns it
	 * 
	 * \param card
	 * \return 
	 */
	AirliftCard* AirliftCard::operator=(const AirliftCard& card)
	{
		return new AirliftCard(card);
	}

	/**
	 * Play function
	 *
	 */
	void AirliftCard::play()
	{
		cout << "Playing AirliftCard" << endl;
	}

	// Diplomacy Cards
	/**
	 * Default constructor
	 * 
	 */
	DiplomacyCard::DiplomacyCard() : Card()
	{
		name = new std::string("DiplomacyCard");
	}

	/**
	 * Copy Constructor
	 * 
	 * \param dCard
	 */
	DiplomacyCard::DiplomacyCard(DiplomacyCard* dCard) : Card(dCard)
	{
	}

	/**
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 * 
	 */
	DiplomacyCard::~DiplomacyCard()
	{

	}

	/**
	 * Makes a copy and assigns it
	 * 
	 * \param card
	 * \return 
	 */
	DiplomacyCard* DiplomacyCard::operator=(const DiplomacyCard& card)
	{
		return new DiplomacyCard(card);
	}

	/**
	 * Play function
	 *
	 */
	void DiplomacyCard::play()
	{
		cout << "Playing DiplomacyCard" << endl;
	}

	// Deck functions

	/**
	 * Default constructor
	 * 
	 */
	Deck::Deck()
	{
		this->fullDeck = new std::vector<Card*>;
		this->drawPile = new std::vector<int*>;
		return;
	}

	/**
	 * Copy constructor
	 * 
	 * \param deck
	 */
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

	/**
	 * Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 *
	 */
	Deck::~Deck()
	{
		fullDeck->clear();
		delete fullDeck;
		drawPile->clear();
		delete drawPile;
	}

	/**
	 * Makes a copy of the passed deck and assigns it
	 * 
	 * \param deck
	 * \return 
	 */
	Deck* Deck::operator=(const Deck& deck)
	{
		return new Deck(deck);
	}

	/**
	 * Adds the passed card to the deck.
	 * 
	 * \param card
	 */
	void Deck::add(Card* card)
	{
		fullDeck->push_back(card);
		int* size = (int*)fullDeck->size();
		drawPile->push_back(size);

	}

	/**
	 * Returns a card based on its ID
	 * 
	 * \param cardID
	 * \return 
	 */
	Card* Deck::getFromCatalog(int* cardID)
	{
		if ((size_t)cardID < fullDeck->size())
		{
			return this->fullDeck->at((size_t)cardID);
		}
		return nullptr;
	}

	/**
	 * Randomly chooses a card from the drawpile and retrieves the stored ID
	 * removes value from the draw pile
	 * 
	 * \return cardID of drawn card
	 */
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

	/**
	 * Takes cardID and adds it to the bottom of the drawpile
	 * 
	 * \param cardID
	 */
	void Deck::returnToDrawPile(int* cardID)
	{
		drawPile->push_back(cardID);
	}

	/**
	 * print deck
	 * 
	 * \param out
	 * \param deck
	 * \return 
	 */
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
	
	/**
	 * Print drawpile for debug reasons
	 * 
	 */
	void Deck::printDrawpile()
	{
		cout << "Here are the contents of the drawpile" << endl;
		cout << "index\tCard ID" << endl;

		int i = 0;
		for (std::vector<int*>::iterator it = drawPile->begin(); it != drawPile->end(); ++it) {

			int* cardID = (*it);
			cout << i++ << "\t" << (int)cardID << endl;
		}
		cout << "----------------";
	}

	// Hand functions
	/**
	 * Constructor with reference to the Deck
	 * 
	 * \param deck
	 */
	Hand::Hand() {

	}
	Hand::Hand(Deck* deck)
	{
		this->deck = deck;
		this->currentHand = new vector<int*>;
	}

	/**
	 * Copy constructor
	 * 
	 * \param hand
	 */
	Hand::Hand(Hand* hand)
	{
		this->deck = new Deck(hand->deck);
		this->currentHand = new vector<int*>;

		for (int i = 0; i < hand->currentHand->size(); i++)
		{
			currentHand->push_back(hand->currentHand->at(i));
		}
	}

	/**
	 * Destructor
	 * 
	 */
	Hand::~Hand()
	{
		delete deck;
		currentHand->clear();
		delete  currentHand;
	}

	/**
	 * Makes a copy and assigns it
	 * 
	 * \param hand
	 * \return 
	 */
	Hand* Hand::operator=(const Hand& hand)
	{
		return new Hand(hand);
	}

	/**
	 * Adds a cardID to the hand
	 * 
	 * \param cardId
	 */
	void Hand::addCard(int* cardId)
	{
		currentHand->push_back(cardId);
	}

	/**
	 * Plays card at hand index
	 * 
	 * \param index Index of the card to be played
	 */
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

	/**
	 * \return currentHand
	 */
	vector<int*>* Hand::getCurrentHand()
	{
		return this->currentHand;
	}

	/**
	 * Stream operator that prints the hand contents
	 * 
	 * \param out
	 * \param hand
	 * \return 
	 */
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
