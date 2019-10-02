#include <QCoreApplication>
#include <QDebug>
#include <map>

class A {
protected:
    static const uint layer_ = 255;
public:
    virtual const uint layer() { return layer_; }
    bool operator < ( A& a ) { return layer() < a.layer(); }
    bool operator > ( A& a ) { return layer() > a.layer(); }
    operator uint () { return layer(); }
};

class B : public A {
    static const uint layer_ = 1;
public:
    const uint layer() { return layer_; }
};

class C : public A {
    static const uint layer_ = 2;
public:
    const uint layer() { return layer_; }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    A a,a1,a2; B b,b1; C c,c1,c2;

    qDebug() << a.layer() << b.layer() << c.layer() ;
    qDebug() << (a < b) << (b < a) << (a < c) << (c < a) << (b < c);

    std::multimap<uint, A&, std::less<uint>> map;
    map.insert(  std::pair<uint, A&>( a.layer(), a ) );
    map.insert(  std::pair<uint, A&>( a1.layer(), a1 ) );

    map.insert(  std::pair<uint, A&>( b.layer(), b ) );
    map.insert(  std::pair<uint, A&>( b1.layer(), b1 ) );
    map.insert(  std::pair<uint, A&>( c.layer(), c ) );
    map.insert(  std::pair<uint, A&>( c1.layer(), c1 ) );
    map.insert(  std::pair<uint, A&>( c2.layer(), c2 ) );

    map.insert(  std::pair<uint, A&>( a2.layer(), a2 ) );

    std::multimap<uint, A&>::iterator it= map.begin();
    for ( it; it != map.end(); ++it ) {
        qDebug() << it->first;
    }
    
    return app.exec();
}
