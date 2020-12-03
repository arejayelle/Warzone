#pragma once

#include "Player.h"
#include "GameObservers.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


class Player;
class Territory;
class StatsObservable;


class Order {
public:
	Order();
	Order(Player* player);
	Order(Order* other);
	~Order();

	virtual bool execute() = 0;
	virtual bool validate();
	virtual Order* clone() = 0;
	virtual std::string toString() const;
	virtual int getPriority();

private:
	friend std::ostream& operator<<(std::ostream &strm, const Order &o);

protected:
	Player* player;  // The player who created the order.
	Order& operator= (const Order& o);
};


class DeployOrder : public Order {
public:
	DeployOrder(Player* player, int numArmies, Territory* target);
	DeployOrder(DeployOrder* other);
	~DeployOrder();
	
	bool validate();
	bool execute();
	DeployOrder* clone();
	std::string toString() const;
	int getPriority();

private:
	int numArmies;  // Number of armies to deploy.
	Territory* target;  // Territory to deploy to.

	friend std::ostream& operator<<(std::ostream& strm, const DeployOrder& o);
	DeployOrder& operator= (const DeployOrder& o);
};


class AdvanceOrder : public Order {
public:
	AdvanceOrder(Player* player, int numArmies, Territory* source, Territory* target);
	AdvanceOrder(AdvanceOrder* other);
	~AdvanceOrder();

	bool validate();
	bool execute();
	AdvanceOrder* clone();
	void battle();  // The battle simulation sequence.
	std::string toString() const;
	int getPriority();
	static StatsObservable* statsObservable;

private:
	int numArmies;  // Number of armies to advance.
	Territory* source;  // Origin territory.
	Territory* target;  // Destination territory.

	friend std::ostream& operator<<(std::ostream& strm, const AdvanceOrder& o);
	AdvanceOrder& operator= (const AdvanceOrder& o);
};


class BombOrder : public Order {
public:
	BombOrder(Player* player, Territory* target);
	BombOrder(BombOrder* other);
	~BombOrder();

	bool validate();
	bool execute();
	BombOrder* clone();
	std::string toString() const;
	int getPriority();

private:
	Territory* target;  // The territory to bomb.

	friend std::ostream& operator<<(std::ostream& strm, const BombOrder& o);
	BombOrder& operator= (const BombOrder& o);
};


class BlockadeOrder : public Order {
public:
	BlockadeOrder(Player* player, Territory* target);
	BlockadeOrder(BlockadeOrder* other);
	~BlockadeOrder();

	bool validate();
	bool execute();
	BlockadeOrder* clone();
	std::string toString() const;
	int getPriority();

private:
	Territory* target;  // The territory where blockade will be applied (becomes neutral territory).

	friend std::ostream& operator<<(std::ostream& strm, const BlockadeOrder& o);
	BlockadeOrder& operator= (const BlockadeOrder& o);
};


class AirliftOrder : public Order {
public:
	AirliftOrder(Player* player, int numArmies, Territory* source, Territory* target);
	AirliftOrder(AirliftOrder* other);
	~AirliftOrder();

	bool validate();
	bool execute();
	AirliftOrder* clone();
	std::string toString() const;
	int getPriority();

private:
	int numArmies;  // Number of armies to transport.
	Territory* source;  // Origin territory.
	Territory* target;  // Destination territory.

	friend std::ostream& operator<<(std::ostream& strm, const AirliftOrder& o);
	AirliftOrder& operator= (const AirliftOrder& o);
};


class NegotiateOrder : public Order {
public:
	NegotiateOrder(Player* player, Player* targeted);
	NegotiateOrder(NegotiateOrder* other);
	~NegotiateOrder();

	bool validate();
	bool execute();
	NegotiateOrder* clone();
	std::string toString() const;
	int getPriority();

private:
	Player* targeted;  // The player which the negotiation will take place with.

	friend std::ostream& operator<<(std::ostream& strm, const NegotiateOrder& o);
	NegotiateOrder& operator= (const NegotiateOrder& o);
};


class OrdersList {
public:
	OrdersList();
	OrdersList(OrdersList* other);
	~OrdersList();

	int size();
	void add(Order* newOrder);
	Order* pop();
	Order* peek();
	Order* remove(int index);
	bool move(int oldIndex, int newIndex);
	std::string print();
	bool executeAll();

private:
	std::vector<Order*> orders;
	friend std::ostream& operator<<(std::ostream& strm, const OrdersList& o);
	OrdersList* operator= (const OrdersList& o);
};
