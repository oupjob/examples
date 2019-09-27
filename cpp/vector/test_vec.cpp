#include <vector>
#include <iostream>

using namespace std;

int main(void) {
	typedef vector<int> V;
	V v;
	v.reserve( 105 );
	cout << "begin   ) Capacity: " << v.capacity() << " Size: " <<  v.size() << endl;
	
	for( int i = 0; i <= 105; i++ ) {
		v.push_back( i );
	}
	cout << "full    ) Capacity: " << v.capacity() << " Size: " << v.size() << endl;

	v.reserve( 50 );
	cout << "reserve ) Capacity: " << v.capacity() << " Size: " << v.size() << endl;
	
	v.clear();
	cout << "clear   ) Capacity: " << v.capacity() << " Size: " << v.size() << endl;

	return 0;
}
