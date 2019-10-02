#include <iostream>
#include <string>
#include <utility>
#include <limits>

int main()
{
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();
    unsigned long long m = (max - min) * 10;
  
	std::cout << m << " " << min << " " << max << std::endl;   
}
