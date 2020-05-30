#include "Header.h"
#include "Interpolation.h"
#include "Polynom.h"


int main()
{
	cout.precision(25);
	int numb;
	double tmp;
	vector<double> xs;
	vector<double> ys;
	cout << "Enter numbers of point: "; cin >> numb;
	cout << "Enter x values:";
	for (size_t i = 0; i < numb; i++)
	{
		cin >> tmp;
		xs.push_back(tmp);
	}
	cout << "Enter y values:";
	for (size_t i = 0; i < numb; i++)
	{
		cin >> tmp;
		ys.push_back(tmp);
	}
	vector<int_node> points;//({ {1,-1}, {3, 2}, {4,0}, {5,1}, {7, 2} });
	for (int i = 0; i < xs.size(); i++)
	{
		points.push_back({ xs[i], ys[i] });
	}
	Lagrange_comp c(points);
	Newton_comp newt(points);
	Smallest_square a(points);
	cout << "RESULTS:\nLagrange polynom:\n";
	c.Polynom_calculate();
	c.Print();
	cout << "Newton polynoms (forward and backward):\n";
	newt.Polynom_calculate();
	newt.Print();
	cout << "Smallest squares method polynom:\n";
	a.Polynom_calculate();
	a.Print();
	cout << "Error: " << a.Error() << endl;
	cout << "X_i L_n(x)\t\t\tP_n(x)\t\t\t   Q_m(x)\n";
	cout << "X-1 " << c.Value_in_point(points[0].x - ((points[1].x - points[0].x)/2))
		<<" " << newt.Value_in_point(points[0].x - ((points[1].x - points[0].x) / 2))
		<<" " << a.Value_in_point(points[0].x - ((points[1].x - points[0].x) / 2)) << endl;
	for (size_t i = 0; i < points.size()-1; i++)
	{
		cout <<"X_" << i << " " << c.Value_in_point(points[i].x + ((points[i + 1].x - points[i].x) / 2))
			<< " " << newt.Value_in_point(points[i].x + ((points[i + 1].x - points[i].x) / 2))
			<< " " << a.Value_in_point(points[i].x + ((points[i + 1].x - points[i].x) / 2)) << endl;
	}
	cout << "X_n " << c.Value_in_point(points[points.size() - 1].x + ((points[points.size() - 1].x - points[points.size() - 1 - 1].x) / 2))
		<< " " << newt.Value_in_point(points[points.size() - 1].x + ((points[points.size() - 1].x - points[points.size() - 1 - 1].x) / 2))
		<< " " << a.Value_in_point(points[points.size() - 1].x + ((points[points.size() - 1].x - points[points.size() - 1 - 1].x) / 2)) << endl;
	//cout << points.size();
	return EXIT_SUCCESS;
}