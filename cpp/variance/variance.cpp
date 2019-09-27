#include <iostream>
#include <vector>

using namespace std;

struct I {
	virtual int val() = 0;	
};

struct X : public I {
	int x;
    X( int i ) : x( i ) {}
	virtual int val() { return x; }	
};

struct Y : public X {
    Y( int i ) : X( i ) {}
	virtual int val() { return x * x; }	
};

template <typename T> void print( vector<T*>& v ) { 
	int n = v.size();

	for( int i = 0; i < n; i++ ) {
		cout << v[ i ].val() << " ";
	}
	cout << endl;
}

int main( void ) {
	vector<I*> v;
	for( int i = 0; i < 10; i++ )
		v.push_back( new Y( i ) );

	print<Y>( v );
    
    for( int i = 0; i < 10; i++ )
        delete v[ i ];

	return 0;
}
