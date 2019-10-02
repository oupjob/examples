#include <QCoreApplication>
#include <vector>
#include <iostream>
#include <string>

typedef std::vector<int> V;

V::iterator begin() {
    V v;
    return v.begin();
}

V::iterator end() {
    V v;
    return v.end();
}

int main(int argc, char *argv[]) {
    V::iterator i, e;
    i = begin();
    e = end();

    std::cout << ( ( i == e ) ? std::string( "=" ) : std::string( "!=" )  ) << std::endl;

    for(; i != e; ++i ) {
        std::cout << "*\n";
    }
}
