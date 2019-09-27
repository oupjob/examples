#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream is;
	is.open( "./in", ios_base::in | ios_base::ate );
	int n = is.tellg();
	cout << "file size: " << n << endl;
	is.seekg( 2, is.beg );

	char buff[ 256 ];
	while( is ) {
		is.getline( buff, sizeof( buff ) );
		cout << buff << endl;
	}

	is.close();
	return 0;
}
