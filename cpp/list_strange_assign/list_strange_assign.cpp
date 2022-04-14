#include <iostream>
#include <list>
#include <memory>
#include <utility>

using namespace std;

typedef list<shared_ptr<int>> L;

int main()
{
	L l1, l2;
	l2 = std::move(l1);

	return 0;
}
