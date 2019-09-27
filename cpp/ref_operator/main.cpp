#include <iostream>
#include <vector>

using namespace std;

// reference type cast example 
//  cast : struct B -> vector<A>& 

struct A {
	int x;
};

typedef std::vector<A> VA;

struct B {
	VA 	v;

	B() { v.push_back( { 1 } ); v.push_back( { 2 } ); v.push_back( { 3 } ); }
	operator VA& () { return v; }
};

void print( B& b ) {
	VA& v = b;	
	VA::iterator i = v.begin();

	for(; i != v.end(); ++i ) {
		cout << i->x << " "; 
	}
	cout << endl;
}

int main() {
	B b;

	print( b );
	return 0;
}


