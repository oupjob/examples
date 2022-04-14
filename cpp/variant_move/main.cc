#include <iostream>
#include <string>
#include <variant>

using namespace std;

struct A
{
    int x;

    A() : x(1) { cout << "A()" << endl; }
    A(const A& a) { cout << "A(const A&)" << endl; }
    A(const A&& a) { cout << "A(const A&&)" << endl; }
};

typedef std::variant<int, A> var_t;

A f(var_t& v) { return std::move(std::get<A>(v)); } 

int main()
{
    var_t v = A();
    A a = f(v);
}

