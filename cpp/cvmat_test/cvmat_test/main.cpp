#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <iostream>

#define M 2
#define N 8

using namespace std;

template <typename T>
std::pair<T*, cv::Mat> createMat( int m, int n ) {
    cv::Mat mat( m, n, cv::DataType<T>::type );

//    for( int i = 0; i < M; i++ ) {
//        for (int j = 0; j < N; ++j) {
//            m.at( i, j ) = i + j;
//        }
//    }
    mat.zeros( m, n, cv::DataType<T>::type );
    return pair<T*, cv::Mat> ( (int*)mat.data, mat );
}

typedef std::pair<int*, cv::Mat> Ptr2MatPair;

int main(int argc, char *argv[])
{
    Ptr2MatPair p = createMat<int>( M, N );

    uchar* data = p.second.data;
    int*   idata = p.first;

    for( int i = 0; i < M; i++ ) {
        for (int j = 0; j < N; ++j) {
            p.second.at<int>( i, j ) =  i * M + j;
            cout << *( p.first + i * M + j ) << " ";
        }
        cout << endl;
    }

//    for( int i = 0; i < M; i++ ) {
//        for (int j = 0; j < N; ++j) {
//        idata = (int*)( p.second.data );
//        cout << " *p[1] = " << *( p.first + i * M + j )
//             << " m = " << *( idata + i * M + j );
//        }
//        cout << endl;
//    }

    p.second.release();
    cout << "p.second.release(): " << endl;

    for( int i = 0; i < M; i++ ) {
        for (int j = 0; j < N; ++j) {
            cout << *( p.first + i * M + j ) << " ";
        }
        cout << endl;
    }

    cout << "mat( M, N, cv::DataType<int>::type )" << endl;
    cv::Mat mat( M, N, cv::DataType<int>::type ), t;
    mat.zeros( M, N, cv::DataType<int>::type );
    t = mat;

    cout << "ptr(t) = " << (int*)t.data << " <-> "
         << "ptr(mat) = " << (int*)mat.data << endl;

    cout << mat.addref();

    int* md = (int*)mat.data;
    cout << "ptr(md) = " << md << endl;

    mat.release();
    cout << "mat.release()" << endl;
    cout << "ptr(t) = " << (int*)t.data << " <-> "
         << "ptr(mat) = " << (int*)mat.data << endl;

    t.release();
    cout << "t.release()" << endl;
    cout << "ptr(t) = " << (int*)t.data << " <-> "
         << "ptr(mat) = " << (int*)mat.data << endl;

    cout << "order by ptr(md) = " << md << ":" << endl;
    for( int i = 0; i < M; i++ ) {
        for (int j = 0; j < N; ++j) {
            cout << *( md + i * M + j ) << " ";
        }
        cout << endl;
    }

    *( md + 2 ) = 1;

    cout << "order by ptr(md) = " << md << ":" << endl;
    for( int i = 0; i < M; i++ ) {
        for (int j = 0; j < N; ++j) {
            cout << *( md + i * M + j ) << " ";
        }
        cout << endl;
    }


//    cout << "try delete md..." << endl;
//    delete (uchar*)md;
//    cout << "md deleted" << endl;

    cout << "exit 0" << endl;
    return 0;
}
