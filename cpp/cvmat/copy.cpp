#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;

int main() {
	cv::Mat a( 2, 1, cv::DataType<double>::type ), b;

	a.at<double>( 0, 0 ) = 0.2;
	a.at<double>( 0, 1 ) = 0.4;

	b = a.clone();

	cout << b.at<double>( 0, 0 ) << " " << b.at<double>( 0, 1 ) << endl;

	b.at<double>( 0, 0 ) = 1;
	
	cout << a.at<double>( 0, 0 ) << endl;

	return 0;
}
