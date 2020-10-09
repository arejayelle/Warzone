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

private:
	friend ostream& operator<<(ostream& strm, const DeployOrder& o);
};


class AdvanceOrder : public Order {
public:
	AdvanceOrder(Player* player);
	AdvanceOrder(AdvanceOrder* other);
	~AdvanceOrder();

	bool validate();
	bool execute();

private:
	friend ostream& operator<<(ostream& strm, const AdvanceOrder& o);
};


class BombOrder : public Order {
public:
	BombOrder(Player* player);
	BombOrder(BombOrder* other);
	~BombOrder();

	bool validate();
	bool execute();

private:
	friend ostream& operator<<(ostream& strm, const BombOrder& o);
};


class BlockadeOrder : public Order {
public:
	BlockadeOrder(Player* player);
	BlockadeOrder(BlockadeOrder* other);
	~BlockadeOrder();

	bool validate();
	bool execute();

private:
	friend ostream& operator<<(ostream& strm, const BlockadeOrder& o);
};


class AirliftOrder : public Order {
public:
	AirliftOrder(Player* player);
	AirliftOrder(AirliftOrder* other);
	~AirliftOrder();

	bool validate();
	bool execute();

private:
	friend ostream& operator<<(ostream& strm, const AirliftOrder& o);
};


class NegotiateOrder : public Order {
public:
	NegotiateOrder(Player* player);
	NegotiateOrder(NegotiateOrder* other);
	~NegotiateOrder();

	bool validate();
	bool execute();

private:
	friend ostream& operator<<(ostream& strm, const NegotiateOrder& o);
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
	friend ostream& operator<<(ostream& strm, const OrdersList& o);
};
