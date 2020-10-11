#pragma once
#include "Orders.h"
#include "Cards.h"

class Player {
private:
	OrdersList* playerOrdersList;

public:
	Player();

	OrdersList* getOrdersList();
};
