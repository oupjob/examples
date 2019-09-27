#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream ofs;
	ofs.open( "test" );
	ofs << 2.36465e+307 << endl;
	ofs.close();

	return 0;
}
