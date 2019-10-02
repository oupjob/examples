#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QFileDialog>
#include <QString>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this );

    std::string str = (QFileDialog::getOpenFileName(this, "ss", "C:\\Users\\root\\images")).toStdString();
    cv::Mat mat;
    mat = cv::imread( str );

    connect( this->ui->pushButton, SIGNAL(clicked()), ui->widget, SLOT(react()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
