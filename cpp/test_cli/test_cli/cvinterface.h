#ifndef CVINTERFACE_H
#define CVINTERFACE_H

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/operations.hpp>
//#include <opencv2/>

//class CvInterface {
//private:
//    uint stat_vector_dim_;
//    cv::Mat* image_;
//    QString file_name_;

//public:
//    CvInterface( QString & file_name, cv::Mat * image, uint stat_vector_dim = 4 );
//    ~CvInterface();

//    cv::Mat* image() { return image_; }
//    cv::Mat& imageRef() { return *image_; }
//    void setImage( cv::Mat* image ) { image_ = image; }

//    // See http://www.convertdatatypes.com/ for valid cast

//    template <typename Type> void printMat() {
//        for (int i = 0; i < image_->rows; i++) {
//            for (int j = 0; j < image_->cols; j++) {
//                qDebug() << i << ", " << j << "(" <<
//                            (Type)image_->at<cv::Vec3b>(i, j)[0] << ", " <<
//                            (Type)image_->at<cv::Vec3b>(i, j)[1] << ", " <<
//                            (Type)image_->at<cv::Vec3b>(i, j)[2] << ", " <<
//                            (Type)image_->at<cv::Vec3b>(i, j)[3] << ")";
//            }
//        }
//    }

//    template <typename Type> Type * at(uint i, uint j, uint k) { // example: float r = cv_test_instance.at<float>(0,0,3);
//        if ( i > image_->rows || j > image_->cols || k > stat_vector_dim_ - 1 ) return 0;
//        return (Type*)image_->at< cv::Vec3b >(i, j)[k];
//    }
//};

class Test {
public:
    unsigned int a;
    char b;

    void print();
};


#endif // CVINTERFACE_H
