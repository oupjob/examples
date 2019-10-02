#include <QCoreApplication>
#include <iostream>

using namespace std;

// простые функции
int a (int x) { cout << "a" << endl; }
int b (int x) { cout << "b" << endl; }

// функкция возвращающая указатель на функцию
int ( *pt(int code) ) (int) {
    if (code == 1) return a;
    else return b;
}

// массив функций возвращающих указатель на функцию
int (* (*p[2])(int) )(int) = { pt, pt };

int main(int argc, char *argv[])
{
    p[0](1)(0);
    p[1](2)(0);

    QCoreApplication a(argc, argv);

    return a.exec();
}
