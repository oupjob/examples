#include "mainwindow.h"
#include "inputlistmodel.h"
#include "ui_mainwindow.h"

#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent, KeyboardConfig* kbd_config) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    kbd_confg_( kbd_config )
{
    ui->setupUi( this );

    list_model_ = new InputListModel( ui->listView );
    ui->listView->setModel( list_model_ );
    ui->listView->setSelectionMode( QAbstractItemView::NoSelection );

    input_controller_ = new InputController( this, kbd_confg_, list_model_ );
    input_controller_->runObserve();

    connect(
        input_controller_,  SIGNAL( inputHandled() ),
        ui->listView,       SLOT( reset() )
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi( this );
        break;
    default:
        break;
    }
}

void MainWindow::updateListView() {
    ui->listView->update();
}
