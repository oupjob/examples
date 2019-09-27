#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

int main() {
	std::chrono::time_point<std::chrono::system_clock> t0, t1;

	t0 = std::chrono::system_clock::now();	
	std::time_t t0_tt = std::chrono::system_clock::to_time_t( t0 );
	cout 	<< "t0: asctime: " << std::asctime( std::localtime( &t0_tt ) ) 
			<< "seconds: " << t0_tt
			<< endl; 
	cout << endl << "sleep" << endl << endl;

	std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	
	t1 = std::chrono::system_clock::now();
	std::time_t t1_tt = std::chrono::system_clock::to_time_t( t1 );
	cout 	<< "t1: asctime: " << std::asctime( std::localtime( &t1_tt ) )
			<< "seconds: " << t1_tt
			<< endl;
	
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                             (t1-t0).count();

	cout << endl << "elapsed seconds: " << elapsed_seconds << endl;
	return 0;
}
