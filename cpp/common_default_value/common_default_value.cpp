#include <string>
#include <iostream>
#include <vector>
//#include <pair>

using namespace std;

class A {
	std::string 	s;
	int				x;
};

template <typename T> struct InvalidValue 
{
	const T& 	value;
	InvalidValue() : value(T()) {}
	operator const T&() { return value; }
};

int main() {
	int i = InvalidValue<int>();
	string s = InvalidValue<string>();
	vector<string> vs =  InvalidValue<vector<string>>();
	A a = InvalidValue<A>();

	return 0;
}

