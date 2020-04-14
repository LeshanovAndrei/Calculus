#include "Header.h"
#include "Interpolation.h"
#include "Polynom.h"


int main()
{
	vector<double> points({ -2, -1, 0, 1, 3 });
	vector<double> values({ 0, 3, 5, 7, 4 });
	Lagrange_comp c(points, values);
	c.Polynom_calculate();
	c.Print();
	return EXIT_SUCCESS;
}