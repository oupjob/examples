#include <string>
#include <iostream>

struct Named {
	char*	name;
};

char* f() {
	std::string s = "Hello!";
	return const_cast<char*>( s.c_str() );
}

using namespace std;

int main () {
	string s = "Name1";
	Named a = { const_cast<char*>( s.c_str() ) };
	
	s[2] = 'M';

	cout << a.name << endl;

	return 0;
}
