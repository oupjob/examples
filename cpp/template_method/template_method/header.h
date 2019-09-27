#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <list>

class A
{
public:
    virtual ~A() {}
    typedef std::list<A*> Children;

    virtual const A* get( const std::string& n ) const = 0;
    template<typename Pred> const A* getByPred( Pred p ) const {
        return ( p( this ) ) ? this : NULL;
    }

    virtual Children::iterator begin() { return Children::iterator(); }
    virtual Children::iterator end() { return Children::iterator(); }

    virtual std::string getName() const { return ""; }
};

class B : public A {
protected:
    std::string     name_;
public:
    B( const std::string& name ) : name_( name ) {}
    virtual ~B() {
        Children::iterator it = children_.begin();
        for(; it != children_.end(); ++it )
            delete *it;
    }

    Children        children_;
    template<typename Pred> const A* getByPred( Pred p ) const {
        if ( p( this ) ) return this;
        Children::const_iterator it = children_.begin();
        for(; it != children_.end(); ++it )
            if ( p( *it ) ) return *it;
    }
    virtual Children::iterator begin() { return children_.begin(); }
    virtual Children::iterator end() { return children_.end(); }

    std::string getName() const { return name_; }


    void insert( A* a ) { children_.push_back( a ); }
    virtual const A* get( const std::string& n ) const;
};

template <typename T> class C : public A {
protected:
    std::string     name_;
    T               value_;
public:
    C( const std::string& name, const T& v ) :
        value_( v ), name_( name )
    {}

    const T& value() { return value_; }

    virtual Children::iterator begin() { return Children::iterator(); }
    virtual Children::iterator end() { return Children::iterator(); }

    std::string getName() const { return name_; }

    virtual const A* get( const std::string& n ) const {
        return ( name_ == n ) ? this : NULL;
    }
};

struct PName {
    std::string     name_;
    PName( const std::string& name ) : name_( name ) {}
    bool operator () ( const A* a );
};

#endif // HEADER_H
