#pragma once

#include <vector>
#include <iostream>

using namespace std;


class Player;


class Order {
public:
	Order();
	Order(Player* player);
	Order(Order* other);
	~Order();

	virtual bool validate();
	virtual bool execute();

private:
	friend ostream& operator<<(ostream &strm, const Order &o);

protected:
	Player* player;  // The player who created the order.
};
												

class DeployOrder : public Order {
public:
	DeployOrder(Player* player);
	DeployOrder(DeployOrder* other);
	~DeployOrder();
	
	bool validate();
	bool execute();
};


class AdvanceOrder : public Order {
public:
	AdvanceOrder(Player* player);
	AdvanceOrder(AdvanceOrder* other);
	~AdvanceOrder();

	bool validate();
	bool execute();
};


class BombOrder : public Order {
public:
	BombOrder(Player* player);
	BombOrder(BombOrder* other);
	~BombOrder();

	bool validate();
	bool execute();
};


class BlockadeOrder : public Order {
public:
	BlockadeOrder(Player* player);
	BlockadeOrder(BlockadeOrder* other);
	~BlockadeOrder();

	bool validate();
	bool execute();
};


class AirliftOrder : public Order {
public:
	AirliftOrder(Player* player);
	AirliftOrder(AirliftOrder* other);
	~AirliftOrder();

	bool validate();
	bool execute();
};


class NegotiateOrder : public Order {
public:
	NegotiateOrder(Player* player);
	NegotiateOrder(NegotiateOrder* other);
	~NegotiateOrder();

	bool validate();
	bool execute();
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
	vector<Order*>* orders;
};
