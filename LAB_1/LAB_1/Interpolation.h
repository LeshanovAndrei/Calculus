#pragma once
#include "Header.h"
#include "Polynom.h"


struct int_node
{
	double x;
	double y;
	void operator=(int_node a) { x = a.x; y = a.y; }
};

class Computation
{
protected:
	Computation(vector<int_node> interpolation_nodes);

	virtual void Polynom_calculate() = 0;
	virtual double Value_in_point(double x) = 0;

	vector<int_node> interpolation_nodes;
	int n;
	bool calculated;

};

class Lagrange_comp : public Computation
{
public:
	Lagrange_comp(vector<int_node> interpolation_nodes) :Computation(interpolation_nodes) {}
	virtual void Polynom_calculate();
	virtual double Value_in_point(double x);
	void Print() { if (calculated) Lag_pol.Print(); }
private:

	Polynom& l_i(int i);


	Polynom Lag_pol;
};



class Newton_comp : public Computation
{
public:
	Newton_comp(vector<int_node> interpolation_nodes) :Computation(interpolation_nodes) {}
	virtual void Polynom_calculate();
	virtual double Value_in_point(double x);
	void Print() { if (calculated) { New_pol_forward.Print();  New_pol_backward.Print(); } }

private:
	Polynom& Newton_poly_forward();
	Polynom& Newton_poly_backward();
	double divided_diff(vector<int_node>);
	Polynom New_pol_forward;
	Polynom New_pol_backward;
};



//уг бннаые врн рср опнхяундхр йюйхе-рн яреоемх л м ъ ме унвс дюире опнярн онявхрюрэ
class Smallest_square : public Computation
{
public:



private:

};