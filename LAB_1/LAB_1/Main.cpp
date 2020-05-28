#include "Header.h"
#include "Interpolation.h"
#include "Polynom.h"


int main()
{
	vector<int_node> points({ {-2,0}, {-1, 3}, {0,5}, {1,7}, {2, 4} });
	Newton_comp newton(points);
	Lagrange_comp lagr(points);
	newton.Polynom_calculate();
	lagr.Polynom_calculate();
	lagr.Print();
	newton.Print();
	return EXIT_SUCCESS;
}