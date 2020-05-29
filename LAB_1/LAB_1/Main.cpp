#include "Header.h"
#include "Interpolation.h"
#include "Polynom.h"


int main()
{
	cout.precision(25);
	vector<int_node> points({ {1,-1}, {3, 2}, {4,0}, {5,1}, {7, 2} });
	Lagrange_comp c(points);
	Newton_comp newt(points);
	c.Polynom_calculate();
	c.Print();
	newt.Polynom_calculate();
	newt.Print();
	//cout << points.size();
	return EXIT_SUCCESS;
}