#include <iostream>
#include <string>

using namespace std;

struct A
{
	int* x;
	A() { x = new int[10]; }
	~A() { if (x) delete [] x; }
};

union U
{
	int m;
	A a;
	string s;

	U() { m = 0; }
	~U() {}
};

int main()
{
	U u;
	u.s = "12345678901234567890";

	u.a = A();
	for(size_t i = 0; i < 10; ++i)
		u.a.x[i] = 1 << i;

	u.s = "aaaaaaa";

	return 0;
}
