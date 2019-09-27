#include "header.h"

bool PName::operator ()( const A* a ) {
    return a->getName() == name_;
}

const A* B::get( const std::string& n ) const {
    Children::const_iterator it = children_.begin();
    for(; it != children_.end(); ++it )
        if ( ( *it )->getName() == n ) return *it;

    return 0;
}

//const A* C::get( const std::string& n ) const
