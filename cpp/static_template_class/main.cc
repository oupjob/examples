#include <iostream>
#include <array>

using namespace std;


struct A { uint32_t x; };
struct B { uint32_t x; };

template <typename T, size_t size>
class F
{
public:
	static uint32_t get_index_by_x(const array<T, size>& arr, uint32_t x);
};


template <typename T, size_t size>
uint32_t F<T, size>::get_index_by_x(const array<T, size>& arr, uint32_t x)
{
	for(size_t i = 0; i < size; ++i)
	{
		if (arr[i].x == x)
			return i;
	}

	return size;
}


int main()
{
	array<A, 3> a; //  = { { 1 }, { 2 }, { 3 } };
	a[0] = { 1 }; a[1] = { 2 }; a[2] = { 3 };
	array<B, 3> b; //  = { { 4 }, { 5 }, { 6 } };
	b[0] = { 3 }; b[1] = { 4 }; b[2] = { 5 };
	uint32_t i;

	i = F<A, 3>::get_index_by_x(a, 2);
	cout << "get_index_by_x(a, 2) : " << i << endl;

	i = F<B, 3>::get_index_by_x(b, 5);
	cout << "get_index_by_x(b, 5) : " << i << endl;

	return 0;
}
