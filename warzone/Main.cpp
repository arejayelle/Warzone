#include "Main.h"


int main()
{
	return OrdersDriver::main()
		| GameLoopDriver::main();
}
