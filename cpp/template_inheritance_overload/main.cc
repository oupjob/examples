#include <iostream>
#include <string>


using namespace std;


struct A
{
	template <typename T>
	void f(const T& n);
};

template <typename T>
void A::f(const T& n)
{
	cout << "A::f(n = " << n << ")\n"; 
}

struct B : public A
{
	template <typename T>
	void f(const T& n);

	void g();
};

template <>
void B::f<string>(const string& n)
{
	cout << "B::f<string>(n = " << n << ")\n"; 
}

void B::g()
{
	A::f<int>(3);
}

int main()
{
	B b;
	b.f<string>("aaa");
// 	b.f<int>(3);
	b.g();

	return 0;
}
