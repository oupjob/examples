#ifndef MY_LINE_H
#define MY_LINE_H

#include <opencv2/core/core.hpp>

namespace MathStructs {

// class for parametric line equation
//  math def:
//      / x = x_1 + lambda * e_1
//   l: { y = y_1 + lambda * e_1
//      | ...
//      \ z = z_1 + lambda * e_1
// where :
//  (x, y, ... , z) is a p0_;
//  (x_1, y_1, ... , z_1) is a p1_;

template<typename T, int n> class ParametricLineEquation
{
public:
    typedef cv::Vec<T, n> PointT;
private:
    PointT p_;  // end point
    PointT e_;  // directing vector

    inline void getPoint( const T& lambda, PointT& a ) {
        a = p_ + lambda * e_;
    }

public:
//    ParametricLineEquation( const PointT* mat );

    ParametricLineEquation() : p_ ( PointT() ), e_( PointT() ) {
        p_.zeros();
        e_.eye();
    }
    ParametricLineEquation(
        const PointT&  p,
        const PointT&  e
    ) {
        p_ = p; e_ = e;
    }

    PointT getPoint( const T& lambda ) const {
        PointT a( e_ );
        getPoint( lambda, a );
        return a;
    }

    PointT operator()( const T& lambda ) {
        PointT a( e_ );
        getPoint( lambda, a );
        return a;
    }

    void setE( const PointT& e ) { e_ = e; }
    void setP( const PointT& p ) { p_ = p; }

    const PointT& getE() const { return e_; }
    const PointT& getP() const { return p_; }
};

void testParametricLineEquation();
}

using namespace MathStructs;

class PainterLineSystem {
public:
    typedef cv::Vec<int, 2>                 PointT;
    typedef std::pair<PointT&, PointT&>     PointPair;
    typedef ParametricLineEquation<int, 2>  LineEqT;
    typedef std::pair<LineEqT&, LineEqT&>   LineEqTPair;

private:
    LineEqT         line_;
    LineEqT::PointT p_next_;
    int             h_;

public:
    PainterLineSystem( int h ) : h_( h ) {
            line_.setE( PointT( 1, 1 ) );
            line_.setP( PointT( 1, 1 ) );
//            p_next_( -1, -1 );
        }

    void setLine( const PointT& p, const PointT& e ) {
        line_.setP( p ); line_.setE( e );
    }

    const LineEqT& getLine() const { return line_; }

    void setLine( int p_x, int p_y, int e_x, int e_y );
    void setStep( const int& h ) { h_ = h; }

    void next( int x, int y, bool scale_up );
};

void testPainterLineSystem();
#endif // MY_LINE_H
