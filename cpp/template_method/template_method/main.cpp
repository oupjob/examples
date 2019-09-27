#include <iostream>

using namespace std;

#include "header.h"

int main()
{
    B b( "b" );
    b.insert( new C<int>( "c1", 1 ) );
    b.insert( new C<int>( "c2", 2 ) );
    b.insert( new C<string>( "c3", "3" ) );

    const A* a = b.getByPred( PName( "c2" ) );

    cout << a->getName() << endl;
    cout << a->getByPred( PName( "c2" ) )->getName() << endl;

    return 0;
}

