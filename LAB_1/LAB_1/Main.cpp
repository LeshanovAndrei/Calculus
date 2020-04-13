#include "Header.h"
#include "Interpolation.h"


auto main() -> int
{
	Polynom a(*(new vector<node>({ { 0, 2 }, {10, 3} })));
	Polynom b(*(new vector<node>({ {-5, 2} , {15, 4} })));
	Polynom x = a + b;
	x.Print();

	return EXIT_SUCCESS;
}