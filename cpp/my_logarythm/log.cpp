#include <cmath>
#include <iostream>


using namespace std;

double log(double base, double x)
{
	return std::log(x) / std::log(base);
}

int main()
{
	size_t y = log(2, 1);
	cout << y << endl;
	return 0;
}


