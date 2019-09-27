#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main () {
	vector<int> a = { 1, 2, 3, 5 }, b = { 1, 3, 6, 7 }, c;
	c.reserve( 8 );
	std::merge( a.begin(), a.end(), b.begin(), b.end(), std::back_inserter( c ) );
	for( auto c_it = c.begin(); c_it != c.end(); ++c_it ) {
		cout << *c_it << " ";
	}  	
	cout << endl;
	return 0;
}
