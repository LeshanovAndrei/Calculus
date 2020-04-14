#include "Interpolation.h"


Computation::Computation(vector<int_node> interpolation_nodes):
	interpolation_nodes(interpolation_nodes),
	calculated(0)
{
	n = interpolation_nodes.size();
}



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
	Polynom* res = new Polynom(*(new vector<poly_node>({ {1, 0} })));
	for (int j = 0; j < n; j++)
	{
		if (j != i)
		{
			Polynom* tmp = new Polynom(*(new vector<poly_node>({ {-interpolation_nodes[j].x, 0},  {1, 1} })));
			*tmp = *tmp / (interpolation_nodes[i].x - interpolation_nodes[j].x);
			*res = *res * *tmp;
		}

	}
	return *res;
}

void Lagrange_comp::Polynom_calculate()
{
	for (int i = 0; i < n; i++)
	{
		Lag_pol = Lag_pol + (l_i(i) * interpolation_nodes[i].y);
	}
	calculated = 1;
}


double Newton_comp::divided_diff(vector<int_node> ixys)
{
	if (ixys.size() == 2)
	{
		return (ixys[0].y - ixys[ixys.size() - 1].y) / (ixys[0].x - ixys[ixys.size() - 1].x);
	}
	vector<int_node> tmp1, tmp2;
	for (size_t i = 1; i < ixys.size(); i++)
	{
		tmp1.push_back(ixys[i]);
		tmp2.push_back(ixys[i - 1]);
	}
	return (divided_diff(tmp1)- divided_diff(tmp2))/ (ixys[0].x - ixys[ixys.size() - 1].x);
}