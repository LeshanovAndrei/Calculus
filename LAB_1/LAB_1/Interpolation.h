#pragma once
#include "Header.h"
#include "Polynom.h"


class Computation
{
protected:
	Computation(vector<double> interpolation_nodes, vector<double> values_in_nodes);

	virtual void Polynom_calculate() = 0;
	virtual double Value_in_point(double x) = 0;

	vector<double> interpolation_nodes;
	vector<double> values_in_nodes;
	int n;
	bool calculated;

};

class Lagrange_comp : public Computation
{
public:
	Lagrange_comp(vector<double> interpolation_nodes, vector<double> values_in_nodes) :Computation(interpolation_nodes, values_in_nodes) {}
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

	virtual void Polynom_calculate();
	virtual double Value_in_point(double x);
	

private:
	
	Polynom New_in_div_diff;
	Polynom New_in_fin_diff;
};



//уг бннаые врн рср опнхяундхр йюйхе-рн яреоемх л м ъ ме унвс дюире опнярн онявхрюрэ
class Smallest_square : public Computation
{
public:



private:

};