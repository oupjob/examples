// Example program
#include <iostream>
#include <string>

using namespace std;

struct A 
{
    string s;
    int n;
    
    A(string _s, int _n) : s(_s), n(_n) {};
    A(const A& src) : s(src.s), n(src.n) { cout << "A::A(const A&)" << endl; }
//    A(A&& src) : s(src.s), n(std::move(src.n)) { cout << "A::A(A&&)" << endl; }
};

using pair_t = std::pair<int, A>;

int main()
{
    A a {"1", 1};
    pair_t p1{1, a}, p2 = std::move(p1);
    
    return 0;
}
