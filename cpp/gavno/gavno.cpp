#include <iostream>

using namespace std;

typedef void(*Func)( void(*)( ) );

void f( Func g )  {
	cout << "f" << endl;
	g( &f );
}

// void blyad( void (*callback)( void (*)( void (*)( void (*)() ) ) ) {
//	cout << "Suka, ";
//	callback( &blyad );
// }

int main() {
	// suka( &suka );
	f( f );
	return 0;
}
