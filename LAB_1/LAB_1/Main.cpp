#include "Header.h"
#include "Interpolation.h"
#include "Polynom.h"


int main()
{
	vector<int_node> points({ {-2,0}, {-1, 3}, {0,5}, {1,7}, {3, 4} });
	Lagrange_comp c(points);
	c.Polynom_calculate();
	c.Print();
	return EXIT_SUCCESS;
}