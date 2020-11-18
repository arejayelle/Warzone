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
	std::string toString() const;
	int getPriority();

private:
	int numArmies;
	Territory* target;

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
	void battle();
	std::string toString() const;
	int getPriority();
	static StatsObservable* statsObservable;

private:
	int numArmies;
	Territory* source;
	Territory* target;

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
	std::string toString() const;
	int getPriority();

private:
	Territory* target;

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
	std::string toString() const;
	int getPriority();

private:
	Territory* target;

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
	std::string toString() const;
	int getPriority();

private:
	int numArmies;
	Territory* source;
	Territory* target;

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
	std::string toString() const;
	int getPriority();

private:
	Player* targeted;

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
	void print();
	bool executeAll();

private:
	std::vector<Order*> orders;
	friend std::ostream& operator<<(std::ostream& strm, const OrdersList& o);
	OrdersList* operator= (const OrdersList& o);
};
