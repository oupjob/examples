#include "my_line.h"
#include <QDebug>

// namespace MathStructs {

#define print_point( p ) qDebug() << p( 0 ) << " " << p( 1 )
#define print_line_pair( lp )\
    print_point( lp.first );

void MathStructs::testParametricLineEquation() {
    cv::Vec<double, 2>
            e( 1, 1 ),
            p( 1, 2 );
    ParametricLineEquation<double, 2> f( p, e );

    for( double t = 0; t < 5; t = t + 0.5 ) {
        p = f( t );
        print_point( p );
    }
}

#define ABS 4

void testPainterLineSystem() {
    PainterLineSystem pls( 1 );

    for( int x = 0; x <= ABS ; x += 2 ) {
        for( int y = 0; y <= ABS; y += 2 ) {
            pls.next( x, y, true );

            const PainterLineSystem::LineEqT& line = pls.getLine();
            const PainterLineSystem::LineEqT::PointT
                &p = line.getP(), &e = line.getE();

            qDebug()
                << "next( " << x << ", " << y << " )"
                << " p = " << p( 0 ) << p( 1 )
                << " e = " << e( 0 ) << p( 0 );
        }
    }
}

void PainterLineSystem::next( int x, int y, bool scale_up ) {
//    p_next_ = LineEqT::PointT( x, y );
    LineEqT::PointT e_next( x - line_.getP()( 0 ), y - line_.getP()( 1 ) ), p;

    LineEqT line_for_center( line_.getP(), e_next );

    p = line_for_center( h_ );
//    e_next ( x - line_.getP()( 0 ), y - line_.getP()( 1 ) );

    line_ = LineEqT( p, e_next );
}
// }
