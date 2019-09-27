#include <iostream>
#include <string>

struct A {
    int x;
    int y;
    std::string s;
};

using namespace std;

template<typename T>
void print_sizeof(const std::string& tp_name) {
    cout << "sizeof(" << tp_name << ") is " << sizeof(T) << endl;    
}

int main()
{   
    print_sizeof<A>("A");
    print_sizeof<A&>("A&");
    print_sizeof<A*>("A*");
	print_sizeof<std::string>("std::string");	
	print_sizeof<int>("int");   
 
    return 0;
}
