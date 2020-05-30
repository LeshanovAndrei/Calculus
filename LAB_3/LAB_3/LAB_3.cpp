#include "Calculator.h"
//x^3+x-3
int main()
{
	setlocale(LC_ALL, "ru");
	
	Calculator a;
	a.Set();
	cout << "\nПриближенное значение корня методом:\n\n";
	a.Bisection_method();
	a.Fixed_point_iteration();
	a.Newton();
	a.Secant_method();
	//a.Combined();


	system("pause");
	return 0;
}

