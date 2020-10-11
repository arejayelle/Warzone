#include "Main.h"

int main()
{
	return Cards::main()
		| MapDriver::main()
		| OrdersDriver::main()
		| MapLoaderDriver::main();
}
