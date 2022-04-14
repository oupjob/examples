#include <iostream>

using namespace std;

struct A 
{
	int		a;
	virtual ~A() {}
	A(int _a) : a(_a) {} 
};

struct B : A 
{
	int 	b;
	B(int a, int _b) : A(a), b(_b) {}
};

int main() 
{
	B b(1, 2);

	cout << b.b << b.a << endl;
}
