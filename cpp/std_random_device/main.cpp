#include <string>
#include <iostream>
#include <random>
#include <limits>


using namespace std;

int main () {
	double lower_bound = std::numeric_limits<double>::min();
  	double upper_bound = std::numeric_limits<double>::max();
  
  	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  	std::default_random_engine re;
	for( int i = 0; i < 10; ++i ) {      
  		double a_random_double = unif(re);
  		cout << a_random_double << endl;
	}
  	return 0;
}
