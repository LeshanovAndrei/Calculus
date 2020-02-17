#include <iostream>
#include <iomanip>
#include "Vctor.h"

using namespace std;

struct point
{
	double x, y;
	
};

double lagrange1(Vctor<point> interpolationPoints, short n, double _x)
{
	double result = 0.0;

	for (short i = 0; i < n; i++)
	{
		double P = 1.0;

		for (short j = 0; j < n; j++)
			if (j != i)
				P *= (_x - interpolationPoints[j].x) / (interpolationPoints[i].x - interpolationPoints[j].x);

		result += P * interpolationPoints[i].y;
	}

	return result;
}

int main()
{
	int n;
	point temp;
	Vctor<point> interpolationPoints;
	cout << "This program demonstrates the Lagrange interpolation method\nPlease, enter the number of interpolation nodes: "; cin >> n;
	cout << "Now enter " << n << " pairs of points like this: x_i y_i\n";
	for (int i = 0; i < n; i++)
	{
		cin >> temp.x >> temp.y;
		interpolationPoints.Add(temp);
	}
	system("cls");
	cout << "Ok, we have this:\n";
	cout <<setw(10) << "X: ";
	for (int i = 0; i < n; i++)
	{
		cout << setw(15) << interpolationPoints[i].x << " ";
	}
	cout << "\n";
	cout << setw(10) << "f(X) = Y: ";
	for (int i = 0; i < n; i++)
	{
		cout <<setw(15) << interpolationPoints[i].y << " ";
	}


	return 0;
}