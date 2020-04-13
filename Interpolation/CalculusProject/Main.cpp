#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;


using calc_type = long double;

struct point
{
	calc_type x, y;
};

//calc_type lagrange_interpolation(const std::vector<point>& base_points, long double x) noexcept; //подсчет в точке
std::vector<calc_type> lagrange(const std::vector<point>& points); // нахождение коэф.

//struct point
//{
//	long double x, y;
//};

// нахождение знаменателя константы при каждой итерации как отдельная функция
calc_type denominator(const size_t i, const vector<point>& vec)
{
	calc_type result = 1;
	const auto x_i = vec[i].x;
	for (auto j = vec.size(); j--;)
		if (i != j)
			result *= x_i - vec[j].x;
	return result;
}

//нахождение базисного полинома Лагранжа при каждой итерации
vector<calc_type> interpolation_polynomial(const size_t i, const vector<point>& points)
{
	auto coef = vector<calc_type>(points.size(), 0);
	coef[0] = 1 / denominator(i, points);
	vector<calc_type> new_coef(points.size());

	for (size_t k = 0; k < points.size(); ++k)
		if (k != i)
		{
			std::fill(new_coef.begin(), new_coef.end(), 0);
			for (auto j = k < i ? k + 1 : k; j--;)
			{
				new_coef[j + 1] += coef[j];
				new_coef[j] -= points[k].x * coef[j];
			}
			coef = new_coef;
		}
	return coef;
}

//основная функция, нахождение полного полинома Лагранжа
vector<calc_type> lagrange(const vector<point>& points)
{
	auto polynomial = vector<calc_type>(points.size(), 0);
	vector<calc_type> coef;
	for (size_t i = 0; i < points.size(); ++i)
	{
		coef = interpolation_polynomial(i, points);
		for (size_t k = 0; k < points.size(); ++k)
			polynomial[k] += points[i].y * coef[k];
	}
	return polynomial;
}

double lagrange(vector<point>& interpolationpoints, long double _x)
{
	auto n = interpolationpoints.size();
	double result = 0;

	for (int i = 0; i < n; i++)
	{
		auto P = interpolationpoints[i].y;
		for (int j = 0; j < n; j++)
			if (j != i)
				P *= (_x - interpolationpoints[j].x) / (interpolationpoints[i].x - interpolationpoints[j].x);
		result += P;
	}
	return result;
}


/*WTFF*/
void polynom_output(vector<calc_type> polynom)
{
	cout << '\n';
	//auto i = polynom.rbegin();
	for (auto i = polynom.size() - 1; i < 0; i--)
	{
		cout << polynom[i] << "x^" << i << " + ";
	}
	cout << polynom[0];
}



int main()
{
	int n;
	long double x;
	point temp;
	vector<point> interpolationpoints;
	cout << "This program demonstrates the Lagrange interpolation method\nPlease, enter the number of interpolation nodes: "; cin >> n;
	cout << "Now enter " << n << " pairs of points like this: x_i y_i\n";
	for (int i = 0; i < n; i++)
	{
		cin >> temp.x >> temp.y;
		interpolationpoints.push_back(temp);
	}
	system("cls");
	cout << "Ok, we have this:\n";
	cout <<setw(10) << "X: ";
	for (int i = 0; i < n; i++)
	{
		cout << setw(15) << interpolationpoints[i].x << " ";
	}
	cout << "\n";
	cout << setw(10) << "f(X) = Y: ";
	for (int i = 0; i < n; i++)
	{
		cout <<setw(15) << interpolationpoints[i].y << " ";
	}

	//polynom_output(lagrange(interpolationpoints));
	cout << "\nEnter x:"; cin >> x;
	cout << "F(" << x <<  ") = "<< setprecision(20) << lagrange(interpolationpoints, x) << "\n";

	/*for (int i = 0; i < n; i++)
	{
		cout << lagrange(interpolationpoints, n, 1)[i] << " ";
	}*/
	return 0;
}