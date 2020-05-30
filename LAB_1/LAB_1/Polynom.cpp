#include "Polynom.h"

template<typename T>
T max(T a, T b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

template<typename T>
T min(T a, T b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}



/*
Высшие степени в начале вектора

*/



	Polynom::~Polynom() { }

	/*Polynom& Polynom:: operator=(Polynom p)
	{
		nodes = p.nodes;
		degree = p.degree;
		return *this;
	}*/

	Polynom& Polynom::operator+(Polynom p)
	{
		Polynom* res = new Polynom(*this);
		for (int i = 0; i < p.nodes.size(); i++)
		{
			res->nodes.push_back(p.nodes[i]);
		}
		sort(res->nodes.begin(), res->nodes.end());
		reverse(res->nodes.begin(), res->nodes.end());
		res->polynomial_simplification();
		return *res;
	}

	Polynom& Polynom::operator-(Polynom p)
	{
		Polynom* res = new Polynom(*this);
		for (size_t i = 0; i < p.nodes.size(); i++)
		{
			p.nodes[i].odd *= -1;
		}
		return *res + p;
	}

	Polynom& Polynom::operator*(Polynom p)
	{
		Polynom* res = new Polynom;
		for (size_t i = 0; i < nodes.size(); i++)
		{
			for (size_t j = 0; j < p.nodes.size(); j++)
			{
				res->nodes.push_back(nodes[i] * p.nodes[j]);
			}
		}
		res->polynomial_simplification();
		return *res;
	}

	Polynom& Polynom::operator/(double p)
	{
		Polynom* res = new Polynom(*this);
		for (size_t i = 0; i < nodes.size(); i++)
		{
			res->nodes[i].odd /= p;
		}
		return *res;
	}

	Polynom& Polynom::operator*(double p)
	{
		Polynom* res = new Polynom(*this);
		for (size_t i = 0; i < nodes.size(); i++)
		{
			res->nodes[i].odd *= p;
		}
		return *res;
	}


	void Polynom::polynomial_simplification()
	{
		sort(nodes.begin(), nodes.end());
		reverse(nodes.begin(), nodes.end());
		if (nodes.size())
		{

		
		for (int i = 0; i < nodes.size() - 1; i++)
		{
			if (nodes[i].degree == nodes[i + 1].degree)
			{
				nodes[i].odd += nodes[i + 1].odd;
				nodes.erase(nodes.begin() + i + 1);
				if (i)
				--i;
			}
			if (nodes[i].odd == 0)
			{
				nodes.erase(nodes.begin() + i);
			}
		}
		if (nodes[nodes.size() - 1].odd == 0)
		{
			nodes.erase(nodes.end() - 1);
		}
	}
	}

	void Polynom::Print()
	{
		
		for (int i = 0; i < nodes.size() - 1; i++)
		{
			cout  << nodes[i].odd << "x^" << nodes[i].degree;
			if (nodes[i + 1].odd >= 0)
			{
				cout << " + ";
			}
			else
			{
				cout << " ";
			}
		}
		cout << nodes[nodes.size() - 1].odd << "x^" << nodes[nodes.size() - 1].degree << "\n";
	}

	double Polynom::value_in_point(double x)
	{
		double res = 0;
		for (int i = 0; i < nodes.size(); i++)
		{
			res += pow(x, nodes[i].degree) * nodes[i].odd;
		}
		return res;
	}