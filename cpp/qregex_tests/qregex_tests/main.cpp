#include <QCoreApplication>
#include <QString>
#include <QRegExp>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString s1( "avada:kedavra:foo:bar" ), s2( "baz|foo" );
    QRegExp r1( "baz|bar" );
    QRegExp r2( "kedavra|foo" );
    QRegExp r3( "foo|kedavra" );

    if ( r1.indexIn( s1 ) != -1 ) {
        qDebug() << "r1: " << r1.capturedTexts();
    }
    if ( r2.indexIn( s1 ) != -1 ) {
        qDebug() << "r2: " << r2.capturedTexts();
    }
    if ( r2.indexIn( s2 ) != -1 ) {
        qDebug() << "r2: " << r2.capturedTexts();
    }

    return a.exec();
}
