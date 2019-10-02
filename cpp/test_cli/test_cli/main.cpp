#include <iostream>

using namespace std;

//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "cvinterface.h"
#include <fstream>




int main(int arc, char ** argv)
{
//    cv::Mat img;
   // img = cv::imread(argv[1]);

   // CvInterface cv_iface;
    Test t, u;
    t.a = 1; u.a = 2;
    t.b = 'T'; u.b = 'U';
    std::ofstream _of("1", std::ios::binary);
    if ( _of ) {
        _of.write( reinterpret_cast<char*>( &t ), sizeof(Test) );
    }
    _of.close();

    std::ifstream _if("1", std::ios::binary);
    if ( _if) {
        _if.read( reinterpret_cast<char*>( &u ), sizeof(Test) );
    }
    t.print();

    cout << "Hello World! " << sizeof(Test) << endl;
    return 0;
}

