#include <iostream>
#include <string>
#include <cassert>

int main()
{
    int n = 0, m = 0;
    
   	for(m = 0; m < 100; ++m)
        n += (bool)(m % 2);
    
	assert(n == 50);

	std::cout << n << std::endl;
    
    return 0;
}

