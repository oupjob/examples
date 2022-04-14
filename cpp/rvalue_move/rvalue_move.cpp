#include <iostream>
#include <string>
#include <list>

using namespace std;

struct A 
{
	string 		s;
	int			n;
	int*		p;

	A(A&& a) {
		cout << "mv A(A&& a)" << endl;
		s = std::move(a.s);
		n = a.n;
		p = a.p;

		a.n = 0;
		a.p = 0;
	}
		
	
	A(const A& a) {
		cout << "cp A(const A& a)" << endl;
		s = a.s;
		n = a.n;
		p = new int(n);
	}
	A(const string& _s, int _n) : s(_s), n(_n), p(new int(_n)) {}
};

typedef std::list<A> L;

L f() 
{
	L l { A("s1", 1), A("s2", 2), A("s3", 3) };
	return std::move(l);	
}

A g(string s, int n)
{
	return std::move(A(s, n));
}

void print_l(const L& l)
{
	for(const A& a: l)
		cout << "a = (" << a.s << ", " << a.n << ")" << endl;
}

int main()
{
	// L l;
	L&& l = f();

	A a = g("s4", 4);
	A a1(std::move(a));

	cout << *a.p << endl;

	l.push_back(std::move(a));
	
	print_l(l);
	return 0;
}
