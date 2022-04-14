#include <memory>
#include <iostream>
#include <utility>

using namespace std;



typedef shared_ptr<int*> Ppi;
typedef pair<int, int*> Pair;
typedef shared_ptr<pair<int, int*>> PP;


int main() 
{
	// Error
	// Ppi p = make_shared<int*>(1);
	
	PP p = make_shared<Pair>(Pair(1, nullptr)), p_null = nullptr;
	
	cout << p->first << ", " << p->second << endl;

	return 0;
}
