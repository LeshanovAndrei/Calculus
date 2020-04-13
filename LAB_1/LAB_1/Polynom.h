#pragma once
#include "Header.h"
//#include "Interpolation.h"

template<typename T>
T max(T a, T b);

template<typename T>
T min(T a, T b);


struct node
{
public:
	node(double a, int b) : degree(b), odd(a) {}
	node& operator*(node a)
	{
		node* res = new node(*this);
		res->degree += a.degree;
		res->odd *= a.odd;
		return *res;
	}
	node& operator/(node a)
	{
		node* res = new node(*this);
		res->degree -= a.degree;
		res->odd /= a.odd;
		return *res;
	}
	bool operator>(node a)
	{
		if (degree > a.degree)
			return 1;
		return 0;
	}

	bool operator<(node a)
	{
		if (degree < a.degree)
			return 1;
		return 0;
	}
	bool operator>=(node a)
	{
		if (degree >= a.degree)
			return 1;
		return 0;
	}
	bool operator<=(node a)
	{
		if (degree <= a.degree)
			return 1;
		return 0;
	}

	//private:
	double odd;
	int degree;

};

class Polynom
{
public:
	Polynom(vector<node>& nodess) : nodes(nodess) { polynomial_simplification(); }
	Polynom() {}
	~Polynom();
	//Polynom& operator=(Polynom p);
	Polynom& operator+(Polynom p);
	Polynom& operator-(Polynom p);
	Polynom& operator*(Polynom p);
	void Print();
	//Polynom& operator/(Polynom p); // »ƒ≈“ Õ¿’≈–
	Polynom& operator/(double p);
	Polynom& operator*(double p);
	friend class Computation;
	friend class Lagrange_comp;
	friend class Newton_comp;
	friend class Smallest_square;
private:



	void polynomial_simplification();
	vector<node> nodes;
};

