#pragma once

#include <vector>

using namespace std;

class Order {
public:
	Order();
	Order(Player* player);
	Order(Order* other);
	~Order();

	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (ostream& outStream, const Order& order);

private:
	Player* player;  // The player who created the order.
};

class DeployOrder : public Order { };

class AdvanceOrder : public Order { };

class BombOrder : public Order { };

class BlockadeOrder : public Order { };

class AirliftOrder : public Order { };

class NegotiateOrder : public Order { };

class OrdersList {
public:
	void add(Order* order);
	void remove(int index);  // This is the delete function, but delete is a keyword so I'm calling it remove.
	void move(Order* order, int newIndex);

private:
	vector<Order> orders;
};
