#include <variant>
#include <string>
#include <iostream>


using namespace std;

typedef std::variant<int, string, string> variant_t;

int main()
{
	variant_t var;
	var = "01234567890123456789";
	
	cout << var.get<string>() << " " << var.get<1>() << " (" var.get<2> << ")\n";

	return 0;
}
