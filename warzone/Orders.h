#pragma once

#include "Player.h"

#include <string>
#include <vector>
#include <iostream>


class Player;
class Territory;


class Order {
public:
	Order();
	Order(Player* player);
	Order(Order* other);
	~Order();

	virtual bool execute() = 0;
	virtual bool validate();
	virtual std::string toString() const;

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

private:
	int numArmies;
	Territory* target;

	friend std::ostream& operator<<(std::ostream& strm, const DeployOrder& o);
	DeployOrder& operator= (const DeployOrder& o);
};


class AdvanceOrder : public Order {
public:
	AdvanceOrder(Player* player);
	AdvanceOrder(AdvanceOrder* other);
	~AdvanceOrder();

	bool validate();
	bool execute();
	std::string toString() const;

private:
	friend std::ostream& operator<<(std::ostream& strm, const AdvanceOrder& o);
	AdvanceOrder& operator= (const AdvanceOrder& o);
};


class BombOrder : public Order {
public:
	BombOrder(Player* player);
	BombOrder(BombOrder* other);
	~BombOrder();

	bool validate();
	bool execute();
	std::string toString() const;

private:
	friend std::ostream& operator<<(std::ostream& strm, const BombOrder& o);
	BombOrder& operator= (const BombOrder& o);
};


class BlockadeOrder : public Order {
public:
	BlockadeOrder(Player* player);
	BlockadeOrder(BlockadeOrder* other);
	~BlockadeOrder();

	bool validate();
	bool execute();
	std::string toString() const;

private:
	friend std::ostream& operator<<(std::ostream& strm, const BlockadeOrder& o);
	BlockadeOrder& operator= (const BlockadeOrder& o);
};


class AirliftOrder : public Order {
public:
	AirliftOrder(Player* player);
	AirliftOrder(AirliftOrder* other);
	~AirliftOrder();

	bool validate();
	bool execute();
	std::string toString() const;

private:
	friend std::ostream& operator<<(std::ostream& strm, const AirliftOrder& o);
	AirliftOrder& operator= (const AirliftOrder& o);
};


class NegotiateOrder : public Order {
public:
	NegotiateOrder(Player* player);
	NegotiateOrder(NegotiateOrder* other);
	~NegotiateOrder();

	bool validate();
	bool execute();
	std::string toString() const;

private:
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
	bool remove(int index);
	bool move(int oldIndex, int newIndex);
	void print();
	bool executeAll();

private:
	std::vector<Order*> orders;
	friend std::ostream& operator<<(std::ostream& strm, const OrdersList& o);
	OrdersList* operator= (const OrdersList& o);
};
