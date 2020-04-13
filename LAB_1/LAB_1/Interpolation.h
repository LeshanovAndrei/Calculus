#pragma once
#include "Header.h"

class Computation
{
protected:
	Computation(vector<double> interpolation_nodes, vector<double> values_in_nodes) :
		interpolation_nodes(interpolation_nodes),
		values_in_nodes(values_in_nodes),
		calculated(0)
	{
		n = interpolation_nodes.size();
		if (n == values_in_nodes.size())
		{
			cout << "Error input!\n";
			exit(1);
		}
	}

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

	void Polynom_calculate();
	double Value_in_point(double x);

private:
	Polynom& l_i(int i);


	Polynom Lag_pol;
};

class Newton_comp : public Computation
{
public:

	void Polynom_calculate();
	double Value_in_point(double x);

private:

	Polynom New_pol;
};



//уг бннаые врн рср опнхяундхр йюйхе-рн яреоемх л м ъ ме унвс дюире опнярн онявхрюрэ
class Smallest_square : public Computation
{
public:



private:

};