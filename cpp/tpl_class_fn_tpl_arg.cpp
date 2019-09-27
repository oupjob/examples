// g++ -std=c++14 tpl_class_fn_tpl_arg.cpp -o tpl_class_fn_tpl_arg

#include <iostream>
#include <string>

using namespace std;

int fi(int i, int j)
{
	cout << "f(int, int) " << i << ", " << j << endl;
	return i;
}

int fi(int i, const string& s) {
	cout << "f(int, string) " << i << ", " << s << endl;
	return i;
}

template <typename T> struct Traits {
	typedef T				ArgType;
};

template <> struct Traits<string> {
	typedef const string& 	ArgType;
};

template <typename T, int(f)(int, typename Traits<T>::ArgType), class ATraits = Traits<T> > class A 
{
private:
	int 		i_;
	T 			x_;
public:
	A(int i, T x) : i_(i), x_(x) {}
	void g() {
		f(i_, x_);
	}
};

int main() 
{
	A<int, fi> 			a_int(1, 2);
	A<string, fi> 		a_str(1, "***");

	a_int.g();
	a_str.g();	

	return 0;
}
