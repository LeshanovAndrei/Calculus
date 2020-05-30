#include "Calculator.h"

Calculator::Calculator()
{
	this->eps = 0.00001;
	this->i = new int[5];
}

double Calculator::Module(double a)
{
	if (a < 0)
	{
		a *= -1;
	}
	return a;
}

double Calculator::Max(double *a, int n)
{
	double max = Module(a[0]);
	for (int i = 1; i < n; i++)
	{
		if (Module(a[i]) > max)
		{
			max = Module(a[i]);
		}
	}
	return max;
}

double Calculator::Limits(double A, double a)
{
	double D = 1 + A / Module(a);
	return D;
}

double Calculator::Pow(double a, int n)
{
	double c = a;
	for (int i = 0; i < n - 1; i++)
	{
		c *= a;
	}
	return c;
}

double Calculator::Count_m()
{
	double y;
	double max;
	double Max = F1(A1);
	for (double i = A0 + 1; i <= B0; i++)
	{
		y = 3 * Pow(i, 2) + 1;
		if (Max < y)
		{
			Max = y;
		}
	}
	max = 2.0 / Max;
	return max - 0.0001;
}

double Calculator::F1(double &x)
{
	return 6*Pow(x, 5) - 2*x + 0.5;
}

double Calculator::F2(double &x)
{
	return 30 * Pow(x, 4) - 2;
}

void Calculator::Set()
{
	cout << "Введите степень полинома: ";
	cin >> size;
	size++;
	polynom = new double[size];
	cout << "Введите коэффициенты полинома:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "перед x^" << size - i - 1 << ": ";
		cin >> polynom[i];
	}
	A = Max(polynom, size);
	B1 = B0 = Limits(A, polynom[0]);
	A1 = A0 = B0 * (-1.0);
	cout << "\nИнтервал: [" << A0 << "," << B0 << "]\n";
	m = Count_m();
}

double Calculator::F(double &x)
{
	double y;
	y = Pow(x, 6) - Pow(x, 2) + 0.5*x - 2;
	return y;

}

double Calculator::G(double &x)
{
	double y;
	y = x - m * F(x);
	return y;

}

void Calculator::Bisection_method()//метод деления пополам
{
	i[0] = 0;
	double c;
	while (Module(B1 - A1) > eps)
	{
		c = (A1 + B1) / 2.0;
		if (F(A1)*F(c) < 0)
		{
			B1 = c;
		}
		else
		{
			A1 = c;
		}
		i[0]++;
	}
	cout << "деления пополам: " << c << ". Количество итераций: " << i[0] << endl << endl;
}

void Calculator::Fixed_point_iteration()//метод простой итерации
{
	A1 = A0;
	i[1] = 0;
	while (Module(F(A1)) > eps)
	{
		A1 = G(A1);
		i[1]++;
	}
	cout << "простой итерации: " << A1 << ". Количество итераций: " << i[1] << endl << endl;
}

void Calculator::Newton()//метод касательных
{
	A1 = A0;
	i[2] = 0;
	double tmp = A1 + 2 * eps;
	while (Module(A1 - tmp) > eps) 
	{ 
		tmp = A1;
		A1 = A1 - F(A1) / F1(A1);
		i[2]++;
	}
	cout << "касательных: " << A1 << ". Количество итераций: " << i[2] << endl << endl;
}

void Calculator::Secant_method()//метод хорд
{
	A1 = A0;
	B1 = B0;
	i[3] = 0;
	while (Module(B1 - A1) > eps)
	{
		A1 = B1 - (B1 - A1)*F(B1) / (F(B1) - F(A1));
		B1 = A1 - (A1 - B1)*F(A1) / (F(A1) - F(B1));
		i[3]++;
	}
	cout << "хорд: " << B1 << ". Количество итераций: " << i[3] << endl << endl;
}

/*void Calculator::Combined()//комбинированный
{
	A1 = A0;
	B1 = B0;
	i[4] = 0;
	double c = 0;
	while (Module(B1 - A1) > eps)
	{
		if (F(A1) * F2(A1) < 0)
		{
			A1 += (B1 - A1) / (F(A1) - F(B1))*F(A1); //формулы расчета по методу хорд
			B1 -= F(B1) / F1(B1);
		}
		else
		{
			A1 -= F(A1) / F1(A1); //формулы расчета по методу касательных
			B1 += (B1 - A1) / (F(B1) - F(A1))*F(B1);
		}
		i[4]++;
	}
	c = (A1 + B1) / 2;
	cout << "комбинированным: " << c << ". Количество итераций: " << i[4] << endl << endl;
}*/