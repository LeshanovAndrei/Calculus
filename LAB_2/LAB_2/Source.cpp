#include "Header.h"

computation::computation(double a, double b, double h) :
	a(a),
	b(b),
	h(h),
	n((b - a) / h),
	n2(n * 2)
{}

void computation::Count()
{
	for (int i = 0; i < 5; i++)
	{
		I1[i] = Choice(i, h, n);
		I2[i] = Choice(i, (h / 2), n2);
	}
	for (int i = 0; i < 5; i++)
	{
		if (i == 4)
		{
			r[i] = Runge(i, O2);
		}
		else
		{
			r[i] = Runge(i, O1);
		}
	}
}

void computation::Print()
{
	cout << "\nI = " << I << endl << endl;
	cout << "Trapezoid method with step           h: I = " << I1[0] << ", \th/2: I = " << I2[0] << ". \tError: " << r[0] << endl;
	cout << "Left Rectangle Method with Step      h: I = " << I1[1] << ", \th/2: I = " << I2[1] << ". \tError: " << r[1] << endl;
	cout << "Right Rectangle Method with Step	  h: I = " << I1[2] << ", \th/2: I = " << I2[2] << ". \tError: " << r[2] << endl;
	cout << "Middle Rectangle Method with Step	  h: I = " << I1[3] << ", \th/2: I = " << I2[3] << ". \tError: " << r[3] << endl;
	cout << "Simpson's Method with Step           h: I = " << I1[4] << ", \th/2: I = " << I2[4] << ". \tError: " << r[4] << endl;
	Fragmentation();
	cout << "\nThe number N of partitions of the integration interval:\n" << endl;
	cout << "Trapezoid method              \tN = " << N[0] << ", \tI = " << I1_n[0] << ". \tError: " << r_n[0]  << endl;
	cout << "Left Rectangle Method         \tN = " << N[1] << ", \tI = " << I1_n[1] << ". \tError: " << r_n[1]  << endl;
	cout << "Right Rectangle Method        \tN = " << N[2] << ", \tI = " << I1_n[2] << ". \tError: " << r_n[2]  << endl;
	cout << "Middle Rectangle Method       \tN = " << N[3] << ", \tI = " << I1_n[3] << ". \tError: " << r_n[3]  << endl;
	cout << "Simpson's Method              \tN = " << N[4] << ", \tI = " << I1_n[4] << ". \tError: " << r_n[4]  << endl;
}

double computation::F(double x)
{
	double y;
	y = x / ((3*x + 4)* (3 * x + 4));
	return y;
}

double computation::Trapezium_Method(double h, int n)
{
	double f = 0.0, f1 = 0.0, I, x;
	for (int i = 0; i < n + 1; i++)
	{
		x = a + i * h;
		if (i == 0 || i == n)
		{
			f += F(x);
		}
		else
		{
			f1 += F(x);
		}
	}
	f /= 2;
	f1 += f;
	I = h * f1;
	return I;
}

double computation::Left_Rectangle_Method(double h, int n)
{
	double f = 0.0, I, x;
	for (int i = 0; i < n; i++)
	{
		x = a + i * h;
		f += F(x);
	}
	I = h * f;
	return I;
}

double computation::Right_Rectangle_Method(double h, int n)
{
	double f = 0.0, I, x;
	for (int i = 1; i < n + 1; i++)
	{
		x = a + i * h;
		f += F(x);
	}
	I = h * f;
	return I;
}

double computation::Middle_Rectangle_Method(double h, int n)
{
	double f = 0.0, I, x;
	for (int i = 0; i < n; i++)
	{
		x = a + i * h + h / 2;
		f += F(x);
	}
	I = h * f;
	return I;
}

double computation::Simpson_Method(double h, int n)
{
	double f1 = 0.0, f2 = 0.0, I, x;
	for (int i = 1; i < n; i++)
	{
		x = a + i * h;
		if (i % 2 == 0)
		{
			f2 += F(x);
		}
		else
		{
			f1 += F(x);
		}
	}
	I = (h / 3) * (F(a) + F(b) + 4 * f1 + 2 * f2);
	return I;
}

double computation::Runge(int i, double O)
{
	double R;
	R = O * (I1[i] - I2[i]);
	return R;
}

double computation::Runge1(int i, double O)
{
	double R;
	R = O * (I1_n[i] - I2_n[i]);
	return R;
}

double computation::Module(double g)
{
	if (g < 0)
	{
		g *= -1;
	}
	return g;
}

void computation::Copy()
{
	for (int i = 0; i < 5; i++)
	{
		r_n[i] = Module(r[i]);
	}
}

void computation::Fragmentation()
{
	Copy();
	for (int i = 0; i < 5; i++)
	{
		do
		{
			h = (b - a) / N[i];
			I1_n[i] = Choice(i, h, N[i]);
			I2_n[i] = Choice(i, h / 2, N[i] * 2);
			if (i == 4)
			{
				r_n[i] = Runge1(i, O2);
				N[i] *= 2;
			}
			else
			{
				this->r_n[i] = Runge1(i, O1);
				N[i]++;
			}
		} while (Module(r_n[i]) > e);
		if (i == 4) N[i] /= 2;
		else N[i]--;
	}
}

double computation::Choice(int i, double h, int n)
{
	double A;
	switch (i)
	{
	case 0:
	{
		A = Trapezium_Method(h, n);
		break;
	}
	case 1:
	{
		A = Left_Rectangle_Method(h, n);
		break;
	}
	case 2:
	{
		A = Right_Rectangle_Method(h, n);
		break;
	}
	case 3:
	{
		A = Middle_Rectangle_Method(h, n);
		break;
	}
	case 4:
	{
		A = Simpson_Method(h, n);
		break;
	}
	}
	return A;
}