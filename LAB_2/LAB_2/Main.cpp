#include "Header.h"

using namespace std;



int main()
{
	double x0, x1, h;
	cout << "x_0 = "; cin >> x0;
	cout << "x_1 = "; cin >> x1;
	cout << "h = "; cin >> h;
	computation F(x0, x1, h);
	F.Count();
	F.Print();
	system("pause");
	return EXIT_SUCCESS;
}