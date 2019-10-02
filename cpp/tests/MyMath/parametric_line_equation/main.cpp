#include <QCoreApplication>
#include <QDebug>
#include "my_line.h"

using namespace MathStructs;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    cv::Vec<double, 2> a( 1, 0 ), b( 1, 1 ), c = a + ( 2 * b );
//    qDebug() << c( 0 ) << " " << c( 1 );

    testParametricLineEquation();
    testPainterLineSystem();
    
    return app.exec();
}
