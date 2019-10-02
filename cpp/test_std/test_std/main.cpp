#include <iostream>
#include <map>
#include <stdlib.h>

class S {
public:
    float x;
    S( float _x ) : x(_x) {  }

    bool operator < ( S* a ) {
        return x < a->x;
    }

    bool operator > ( S* a ) {
        return x > a->x;
    }
};

typedef struct {
    bool operator()(S* a, S* b) { return a->x < b->x; }
}  S_less;

bool s_less(S* a, S* b) { return a->x < b->x; }

using namespace std;

S_less sl;

typedef std::pair<std::string, S*> pr;

int main()
{
//    map< string, S* > m( map< string, S* >::value_compare );
    map< string, S* > m;
    S* s1 = new S(0.9), *s2 = new S(1.8), *s3 = new S(5.7);

    m.insert( pr( "c", s1 ) );
    m.insert( pr( "b", s2 ) );
    m.insert( pr( "a", s3 ) );

    std::sort( m.begin(), m.end(), map< string, S* >::value_compare );

    map<string, S*>::iterator it = m.begin();
    for ( it; it != m.end(); ++it )
        cout << (*it).second->x << endl;

    delete s1, s2, s3;

    return 0;
}

