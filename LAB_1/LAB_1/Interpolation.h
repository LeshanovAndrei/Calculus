#pragma once
#include "Header.h"

class Computation
{
protected:
	Computation(vector<double> interpolation_nodes, vector<double> values_in_nodes):
		interpolation_nodes(interpolation_nodes),
		values_in_nodes(values_in_nodes)
	{}

	vector<double> interpolation_nodes;
	vector<double> values_in_nodes;

};

class Lagrange_comp : public Computation
{
public:



private:

};

class Newton_comp : public Computation
{
public:



private:

};

class Smallest_square : public Computation
{
public:



private:

};