#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

enum Type {
	T_B,
	T_C
};

struct A {
	Type 	type;
	union U 
	{
		struct {
			int x;
			int y;
		} b;
		struct {
			string sx;
			string sy;
		} c;

		U() {};
		~U() {};
	} u;

	A() {}
	A(const A& src) { 
		std::memcpy(this, &src, sizeof(A));
	}
};

int main() 
{
	A a1; // {T_B, {1, 2}};
	A a2; // {T_C, {"c", "c"}};

	a1.type = T_B;
	a1.u.b = {1, 2};

	a2.type = T_C;
	a2.u.c = {"sx", "sy"};

	std::vector<A> va;
	va.push_back(a1);
	va.push_back(a2);

	cout << va[0].type << " : " << va[0].u.b.x << ", " << va[0].u.b.y << endl;
	cout << va[1].type << " : " << va[1].u.c.sx << ", " << va[1].u.c.sy << endl;

	return 0;
}
