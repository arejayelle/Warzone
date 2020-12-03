#pragma once
#include <vector>
#include "Map.h"
#include "Orders.h"
#include "Player.h"

class Player;
class BombOrder;
class NegotiateOrder;
class AirliftOrder;
class BlockadeOrder;
class DeployOrder;

class PlayerStrategy
{
public:
	PlayerStrategy();
	PlayerStrategy(const PlayerStrategy& other);
	PlayerStrategy& operator= (const PlayerStrategy& other);
	friend ostream& operator<< (ostream& output, const PlayerStrategy& player);

	virtual const vector<Territory*>* toDefend(Player* player) = 0; //Returns territories to defend. To keep in Player
	virtual const vector<Territory*> toAttack(Player* player) = 0; //Returns territories to attack
	virtual bool issueOrder(Player* player) = 0; // Issues an order to the player's orderList. Returns true if an order was issued

	virtual BombOrder* useBomb(Player* player) = 0;
	virtual NegotiateOrder* useDiplomacy(Player* player) = 0;
	virtual AirliftOrder* useAirlift(Player* player) = 0;
	virtual BlockadeOrder* useBlockade(Player* player) = 0;
	virtual DeployOrder* useReinforcement(Player* player) = 0;
};

/// <summary>
/// Implements the basic strategy developed as part of Assignment 2.
/// Though it is not required in the assignment 3 instructions, it is
/// left in the codebase as a reference for writing the other strategies.
/// </summary>
class DefaultStrategy : public PlayerStrategy
{
public:
	DefaultStrategy();
	DefaultStrategy(const DefaultStrategy& other);
	DefaultStrategy& operator= (const DefaultStrategy& other);
	friend ostream& operator<< (ostream& output, const DefaultStrategy& other);

	const vector<Territory*>* toDefend(Player* player);
	const vector<Territory*> toAttack(Player* player);
	bool issueOrder(Player* player);

	BombOrder* useBomb(Player* player);
	NegotiateOrder* useDiplomacy(Player* player);
	AirliftOrder* useAirlift(Player* player);
	BlockadeOrder* useBlockade(Player* player);
	DeployOrder* useReinforcement(Player* player);
};

class BenevolentComputerStrategy : public PlayerStrategy {
private:
	vector <Territory*> territoriesDefended;
	vector <Territory*> territoriesFortified;
public:
	BenevolentComputerStrategy();
	BenevolentComputerStrategy(const BenevolentComputerStrategy& other);
	BenevolentComputerStrategy& operator= (const BenevolentComputerStrategy& other);
	friend ostream& operator<<(ostream&, const BenevolentComputerStrategy& other);
	Territory* returnStrongestTerritory(vector<Territory*> territory);
	const vector<Territory*>* toDefend(Player* player);
	const vector<Territory*> toAttack(Player* player);
	bool issueOrder(Player* player);

	BombOrder* useBomb(Player* player);
	NegotiateOrder* useDiplomacy(Player* player);
	AirliftOrder* useAirlift(Player* player);
	BlockadeOrder* useBlockade(Player* player);
	DeployOrder* useReinforcement(Player* player);
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(const NeutralPlayerStrategy& other);
	NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& other);
	friend ostream& operator<< (ostream& output, const NeutralPlayerStrategy& other);

	const vector<Territory*>* toDefend(Player* player);
	const vector<Territory*> toAttack(Player* player);
	bool issueOrder(Player* player);

	BombOrder* useBomb(Player* player);
	NegotiateOrder* useDiplomacy(Player* player);
	AirliftOrder* useAirlift(Player* player);
	BlockadeOrder* useBlockade(Player* player);
	DeployOrder* useReinforcement(Player* player);
};
