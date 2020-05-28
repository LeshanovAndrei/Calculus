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
		return ((ixys[0].y - ixys[ixys.size() - 1].y) / (ixys[0].x - ixys[ixys.size() - 1].x));
	}
	vector<int_node> tmp1, tmp2;
	for (size_t i = 1; i < ixys.size(); i++)
	{
		tmp1.push_back(ixys[i]);
		tmp2.push_back(ixys[i - 1]);
	}
	return (divided_diff(tmp1)- divided_diff(tmp2))/ (ixys[0].x - ixys[ixys.size() - 1].x);
}


void Newton_comp::Polynom_calculate()
{
	New_pol_forward = Newton_poly_forward();//работает неправильно
	New_pol_backward = Newton_poly_backward();//не работает совсем
	calculated = 1;
}

Polynom& Newton_comp::Newton_poly_backward()
{
	Polynom* res = new Polynom(*(new vector<poly_node>({ {interpolation_nodes[n - 1].y, 0} })));
	vector<int_node> tmp;
	tmp.push_back(interpolation_nodes[n - 1]);
	Polynom tmpp(*(new vector<poly_node>({ {1, 0} })));
	for (int i = n - 1; i >= 0; i--)
	{
		tmpp = tmpp * *(new Polynom(*(new vector<poly_node>({ {1, 1}, {-interpolation_nodes[i].x ,0} }))));
		tmp.push_back(interpolation_nodes[i]);
		*res = *res + (tmpp * divided_diff(tmp));
	}
	return *res;
}




Polynom& Newton_comp::Newton_poly_forward()
{
	Polynom* res = new Polynom(*(new vector<poly_node>({ {interpolation_nodes[0].y, 0} })));
	vector<int_node> tmp;
	tmp.push_back(interpolation_nodes[0]);
	Polynom tmpp(*(new vector<poly_node>({ {1, 0} })));
	for (size_t i = 1; i < n; i++)
	{
		tmpp = tmpp * *(new Polynom(*(new vector<poly_node>({ {1, 1}, {-interpolation_nodes[i - 1].x ,0} }))));
		tmp.push_back(interpolation_nodes[i]);
		*res = *res + (tmpp * divided_diff(tmp));
	}
	return *res;
}

Newton_comp::Newton_comp(vector<int_node> interpolation_nodes) :Computation(interpolation_nodes) {}

void Newton_comp::Print()
{
	cout << "Newton forward:^\n";//неправильно
	New_pol_forward.Print();
	cout << "Newton backward:^\n";//неопределенные результаты
	New_pol_backward.Print();
}

double Newton_comp::Value_in_point(double x)
{
		double res = 0;
		if (!calculated)
		{
			Polynom_calculate();
		}
		for (int i = 0; i < n; i++)
		{
			res += pow(x, New_pol_forward.nodes[i].degree) * New_pol_forward.nodes[i].odd;
		}
		return res;
}