#include <iostream>
#include <memory>

using namespace std;

struct A
{
	int x;
	int y;
};

struct B : public A
{};


void f(const A& a) { cout << "f(A&) : a.x = " << a.x << ", a.y = " << a.y << endl; }
void f(const B& b) { cout << "f(B&) : b.x = " << b.x << ", b.y = " << b.y << endl; }

int main()
{
//	shared_ptr<A> p = make_shared<B>();
//	p->x = 1;
//	p->y = 2;
	
//	f(*(p.get()));

	A* p = new B();
	p->x = 1;
	p->y = 2;
	f(*p);
}
