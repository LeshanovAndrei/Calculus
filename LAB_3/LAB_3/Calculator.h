#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Calculator
{
	int size, *i;
	double A0, B0, A1, B1, m;
	double *polynom;
	double A;
	double eps;

	double Module(double a);
	double Max(double *a, int n);
	double Limits(double A, double a);
	double Pow(double a, int n);
	double F(double &x);
	double G(double &x);
	double Count_m();
	double F1(double &x);
	double F2(double &x);

public:
	
	Calculator();
	void Set();
	void Bisection_method();//метод деления пополам
	void Fixed_point_iteration();//метод простой итерации
	void Newton();//метод касательных
	void Secant_method();//метод хорд
	//void Combined();//комбинированный


};
