#include "Cards.h"

// Card functions

/**
	 * Card Constructor
	 *
	 */
Card::Card() {
	this->name = "Basic Card";
}

/**
 * Card Copy Constructor
 *
 * \param card to be copied
 */
Card::Card(Card* card)
{
	this->name = card->getName();
}

/**
	 * Card Destructor
	 *
	* Does nothing for now. Does not have any attributes not owned by the parent Card Class
	 *
	 */
Card::~Card()
{

}

/**
	 * Card Play function
	 *
	 */
Order* Card::play(Player* owner)
{
	// TODO
	// return new Order();
	return NULL;
}

/**
	 * \return name of this card
	 */
string Card::getName()
{
	return name;
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
	string name = card.name;
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
	this->name = "Spy Card";
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
Order* SpyCard::play(Player* owner)
{
	cout << "Playing " + name;
	return new NegotiateOrder(owner);
}

// Bomb Cards
/**
	 * BombCard Default Constructor
	 *
	 */
BombCard::BombCard() : Card()
{
	this->name = "BombCard";
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
	 * Creates a Bomb Order
	 */
Order* BombCard::play(Player* owner)
{
	cout << "Playing BombCard" << endl;
	return new BombOrder(owner);
}

// Reinforcement Cards
/**
	 * ReinforcementCard Default Constructor
	 *
	 */
ReinforcementCard::ReinforcementCard() : Card()
{
	name = "ReinforcementCard";
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
Order* ReinforcementCard::play(Player* owner)
{
	cout << "Playing ReinforcementCard" << endl;
	// TODO
	return new DeployOrder(owner, 0, nullptr);
}

// Blockade Cards
/**
 * BlockadeCard Default Constructor
 *
 */
BlockadeCard::BlockadeCard() : Card()
{
	name = "BlockadeCard";
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
Order* BlockadeCard::play(Player* owner)
{
	cout << "Playing BlockadeCard" << endl;
	return new BlockadeOrder(owner);
}

// Airlift Cards
/**
	 * Default constructor
	 *
	 */
AirliftCard::AirliftCard() : Card()
{
	name = "AirliftCard";
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
Order* AirliftCard::play(Player* owner)
{
	cout << "Playing AirliftCard" << endl;
	return new AirliftOrder(owner);
}

// Diplomacy Cards
/**
	 * Default constructor
	 *
	 */
DiplomacyCard::DiplomacyCard() : Card()
{
	name = "DiplomacyCard";
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
Order* DiplomacyCard::play(Player* owner)
{
	cout << "Playing DiplomacyCard" << endl;
	return new NegotiateOrder(owner);
}

Deck::Deck()
{
	this->fullDeck = new vector<Card*>();
}

Deck::Deck(Deck* deck)
{
	const vector<Card*>* realDeck = deck->getDeck();
	for (size_t i = 0; i < realDeck->size() ; i++)
	{
		this->fullDeck->push_back(new Card(realDeck->at(i)));
	}
}

Deck::~Deck()
{
	for (size_t i = 0; i < fullDeck->size(); i++)
	{
		delete (*fullDeck)[i];
	}
	delete fullDeck;
}

Deck* Deck::operator=(const Deck& deck)
{
	return new Deck(deck);
}

const std::vector<Card*>* Deck::getDeck()
{
	return fullDeck;
}

void Deck::add(Card* card)
{
	this->fullDeck->push_back(card);
}

Card* Deck::draw()
{
	srand((unsigned int)time(NULL));
	int drawIndex = rand() % fullDeck->size();

	// Retrieve cardID
	Card* drawnCard = (*fullDeck)[drawIndex];

	// Get iterator at location for erasing
	std::vector<Card*>::iterator it = (*fullDeck).begin() + drawIndex;
	fullDeck->erase(it);
	
	return drawnCard;
}

ostream& operator<<(ostream& out, const Deck& deck)
{
	out << "Here are the contents of the deck" << endl;

	int i = 0;
	for (std::vector<Card*>::iterator it = deck.fullDeck->begin(); it != deck.fullDeck->end(); ++it) {

		out << *(*it) << endl;
	}
	out << "----end of deck ----" << endl;

	return out;
}

Hand::Hand(Deck* deck)
{
	this->deck = deck;
	this->owner = nullptr;
	this->currentHand = new vector<Card*>();
}

Hand::Hand(Deck* deck, Player* player)
{
	this->deck = deck;
	this->owner = player;
	this->currentHand = new vector<Card*>();
}

Hand::Hand(Hand* hand)
{
	this->deck = hand->deck;
	this->owner = hand->owner;
	this->currentHand = new vector<Card*>();
}

Hand::~Hand()
{
	delete this->currentHand;
}

Hand* Hand::operator=(const Hand& hand)
{
	return new Hand(hand);
}

void Hand::addCard(Card* card)
{
	this->currentHand->push_back(card);
}

void Hand::play(int index)
{
	if (index < currentHand->size()) {

		Card* cardToPlay = this->currentHand->at(index);
		Order* newOrder = cardToPlay->play(owner);

		OrdersList* list = owner->getOrdersList();
		list->add(newOrder);

		deck->add(cardToPlay);
		std::vector<Card*>::iterator it = currentHand->begin() + index;
		currentHand->erase(it);
	}
}

const vector<Card*>* Hand::getCurrentHand()
{
	return currentHand;
}

ostream& operator<<(ostream& out, const Hand& hand)
{
	out << "Here are the contents of the Hand" << endl;

	int i = 0;
	for (std::vector<Card*>::iterator it = hand.currentHand->begin(); it != hand.currentHand->end(); ++it) {

		out << *(*it) << endl;
	}
	out << "----end of hand ----" << endl;

	return out;
}