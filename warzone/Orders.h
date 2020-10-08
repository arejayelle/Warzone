#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Player;

class Order {
public:
	Order(Player* player);
	Order(Order* other);
	~Order();

	virtual bool validate();
	virtual bool execute();
	friend ostream& operator<<(ostream& outStream, const Order& order);

protected:
	Player* player;  // The player who created the order.
};
												    
// Each type of order is a subclass of Order.	    
class DeployOrder : public Order {
	DeployOrder(Player* player);
	DeployOrder(DeployOrder* other);
	~DeployOrder();
	
	bool validate();
	bool execute();
};

class AdvanceOrder : public Order { 
	AdvanceOrder(Player* player);
	AdvanceOrder(AdvanceOrder* other);
	~AdvanceOrder();

	bool validate();
	bool execute();
};

class BombOrder : public Order {
	BombOrder(Player* player);
	BombOrder(BombOrder* other);
	~BombOrder();

	bool validate();
	bool execute();
};

class BlockadeOrder : public Order {
	BlockadeOrder(Player* player);
	BlockadeOrder(BlockadeOrder* other);
	~BlockadeOrder();

	bool validate();
	bool execute();
};

class AirliftOrder : public Order {
	AirliftOrder(Player* player);
	AirliftOrder(AirliftOrder* other);
	~AirliftOrder();

	bool validate();
	bool execute();
};

class NegotiateOrder : public Order {
	NegotiateOrder(Player* player);
	NegotiateOrder(NegotiateOrder* other);
	~NegotiateOrder();

	bool validate();
	bool execute();
};

class OrdersList {
public:
	OrdersList(Player* player);
	OrdersList(OrdersList* other);
	~OrdersList();

	void add(Order* newOrder);
	void remove(int index);  // This is the delete function, but delete is a reserved word so I'm calling it remove.
	void move(int oldIndex, int newIndex);
	void print();

private:
	Player* player;
	vector<Order>* orders;
};
