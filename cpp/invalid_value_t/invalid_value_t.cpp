#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename T>
struct InvalidValue
{
	operator T () {return false;}
};

template <typename T> const T invalidValue() 
{
	return sqrt(-1);
}

int main() {
	int i = (int)InvalidValue<int>();
	string s = (string)InvalidValue<string>();
	int * pi = (int*)InvalidValue<int*>();

	return 0;
}
