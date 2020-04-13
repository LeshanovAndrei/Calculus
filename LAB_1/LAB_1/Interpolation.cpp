#include "Interpolation.h"

double Lagrange_comp::Value_in_point(double x)
{
	double res = 0;
	if (!calculated)
	{
		Polynom_calculate();
	}
	for (int i = 0; i < n; i++)
	{
		res += pow(x, Lag_pol.nodes[i].degree) * Lag_pol.nodes[i].odd;
	}
	return res;
}

Polynom& Lagrange_comp::l_i(int i)
{
	Polynom* res = new Polynom;
	for (int j = 0; j < n; i++)
	{
		if (j != i)
		{
			Polynom* tmp = new Polynom(*(new vector<node>({ {interpolation_nodes[j], 0},  {1, 1} })));
			*tmp = *tmp / (interpolation_nodes[i] - interpolation_nodes[j]);
			*res = *res * *tmp;
		}

	}
	return *res;
}

void Lagrange_comp::Polynom_calculate()
{
	for (int i = 0; i < n; i++)
	{
		Lag_pol = Lag_pol + (l_i(i) * values_in_nodes[i]);
	}
	calculated = 1;
}
