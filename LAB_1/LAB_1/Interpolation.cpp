#include "Interpolation.h"


Computation::Computation(vector<int_node> interpolation_nodes):
	interpolation_nodes(interpolation_nodes),
	calculated(0)
{
	n = interpolation_nodes.size() - 1;
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
	for (int j = 0; j <= n; j++)
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
	for (int i = 0; i <= n; i++)
	{
		Lag_pol = Lag_pol + (l_i(i) * interpolation_nodes[i].y);
	}
	calculated = 1;
}


double Newton_comp::divided_diff(vector<int_node> ixys)
{
	if (ixys.size() == 2)
	{
		return (ixys[ixys.size() - 1].y - ixys[0].y) / (ixys[ixys.size() - 1].x - ixys[0].x);
	}
	vector<int_node> tmp1, tmp2;
	for (size_t i = 1; i < ixys.size(); i++)
	{
		tmp1.push_back(ixys[i]);
		tmp2.push_back(ixys[i - 1]);
	}
	return (divided_diff(tmp1)- divided_diff(tmp2))/ (ixys[ixys.size() - 1].x - ixys[0].x);
}


void Newton_comp::Polynom_calculate()
{
	New_pol_forward = Newton_poly_forward();
	New_pol_backward = Newton_poly_backward();
	calculated = 1;
}

Polynom& Newton_comp::Newton_poly_backward()
{
	Polynom* result_polynom = new Polynom(*(new vector<poly_node>({ {interpolation_nodes[n].y, 0} })));
	vector<int_node> divided_diff_arg;
	divided_diff_arg.push_back(interpolation_nodes[n]);
	Polynom tmpp(*(new vector<poly_node>({ {1, 0} })));
	
	for (size_t i = n; i > 0; i--)
	{
		tmpp = tmpp * *(new Polynom(*(new vector<poly_node>({ {1, 1}, {-interpolation_nodes[i].x ,0} }))));
		divided_diff_arg.push_back(interpolation_nodes[i-1]);
		*result_polynom = *result_polynom + (tmpp * divided_diff(divided_diff_arg));
	}
	return *result_polynom;
}

Polynom& Newton_comp::Newton_poly_forward()
{
	Polynom* result_polynom = new Polynom(*(new vector<poly_node>({ {interpolation_nodes[0].y, 0} })));
	vector<int_node> tmp;
	tmp.push_back(interpolation_nodes[0]);
	Polynom tmpp(*(new vector<poly_node>({ {1, 0} })));
	for (size_t i = 1; i < n + 1; i++)
	{
		tmpp = tmpp * *(new Polynom(*(new vector<poly_node>({ {1, 1}, {-interpolation_nodes[i - 1].x ,0} }))));
		tmp.push_back(interpolation_nodes[i]);
		*result_polynom = *result_polynom + (tmpp * divided_diff(tmp));
	}
	return *result_polynom;
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

void Smallest_square::Polynom_calculate()
{
	Smallest_squaró_pol = Smallest_squar();
	calculated = 1;
}

double Smallest_square::c_j(int j)
{
	double res = 0;
	for (size_t i = 0; i <= n; i++)
	{
		res += pow(interpolation_nodes[i].x, j);
	}
	return res;
}

double Smallest_square::d_j(int j)
{
	double res = 0;
	for (size_t i = 0; i <= n; i++)
	{
		res += pow(interpolation_nodes[i].x, j) * interpolation_nodes[i].y;
	}
	return res;
}

double Smallest_square::Value_in_point(double x)
{
	double res = 0;
	if (!calculated)
	{
		Polynom_calculate();
	}
	for (int i = 0; i < n; i++)
	{
		res += pow(x, Smallest_squaró_pol.nodes[i].degree) * Smallest_squaró_pol.nodes[i].odd;
	}
	return res;
}
Polynom& Smallest_square::Smallest_squar()
{
	m = n;
	double** matrix = new double* [m + 1];//ÍÅ ÓÂÅÐÅÍ 
	for (int i = 0; i <= m; i++)
		matrix[i] = new double[m + 2];//ÍÅ ÓÂÅÐÅÍ
	for (size_t i = 0; i <= m; i++)
	{
		for (size_t j = 0; j <= m; j++)
		{
			matrix[i][j] = c_j(j + i);
		}
	}
	for (size_t i = 0; i <= m; i++)
	{
		matrix[i][m + 1] = d_j(i);
	}
	/*cout << "matrix: " << endl;
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < m + 2; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}*/
	double* odds = new double[m + 1];
	odds = Gauss(matrix, m + 1, m + 1);
	//cout << endl;
	vector<poly_node> tmp;
	for (int i = 0; i <= m; i++)
	{
		tmp.push_back({ odds[i], i });
	}
	Polynom* result = new Polynom(tmp);
	return *result;
}