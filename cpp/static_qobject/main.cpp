#include <QCoreApplication>

#include <QDebug>

class A : public QObject {
    Q_OBJECT
public:
    int a;
    void f_sign( int x );
    void f_slot( int x );
signals:
    void sign( int a );
public slots:
    void slot( int b );
};

class B : public QObject {
    Q_OBJECT
public:
    int a;
    void f_sign( int x );
    void f_slot( int x );
signals:
    void sign( int a );
public slots:
    void slot( int b );
};

class Connector : public QObject {
    Q_OBJECT
public:
    void conn( A& a, B& b ) {
        connect( &a, SIGNAL(sign(int&)), &b, SLOT(slot(int&)) );
        connect( &b, SIGNAL(sign(int&)), &a, SLOT(slot(int&)) );
    }
};

class C {
public:
    static void x();
    static void y();
    static A a;
    static B b;
};

void A::f_slot(int x) { qDebug() << "A = " << x; }
void B::f_slot(int x) { qDebug() << "B = " << x; }

void A::f_sign(int x) { emit sign(x); }
void B::f_sign(int x) { emit sign(x); }

void C::x() { a.f_sign(1); }
void C::y() { b.f_sign(1); }

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
