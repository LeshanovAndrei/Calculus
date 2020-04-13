#pragma once

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class computation
{
public:
	computation(double a, double b, double h);

	void Count();

	void Print();

private:
	double a, b, h;
	double I1[5], I2[5], I = 0.07070;
	double r[5], e = 0.0001;
	double r_n[5], I1_n[5], I2_n[5];
	int n, n2, N[5] = { 5,5,5,5,4 };
	const double O1 = 1.0 / 3, O2 = 1.0 / 15;

	double F(double x);

	double Trapezium_Method(double h, int n);

	double Left_Rectangle_Method(double h, int n);

	double Right_Rectangle_Method(double h, int n);

	double Middle_Rectangle_Method(double h, int n);

	double Simpson_Method(double h, int n);

	double Runge(int i, double O);

	double Runge1(int i, double O);

	double Module(double g);

	void Copy();

	void Fragmentation();

	double Choice(int i, double h, int n);
};