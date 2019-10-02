#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treenode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTreeView* tv = ui->treeView;
    TreeNodeModel* model = new TreeNodeModel( tv );

    TreeNode* root = model->getRoot(), *c1, *c2;

    c1 = new TreeNode( root, QPoint( 1, 2 ) );
    c2 = new TreeNode( root, QPoint( 2, 2 ) );

    root->children().push_back( c1 );
    root->children().push_back( c2 );

    c1->children().push_back( new TreeNode( root, QPoint( 4, 6 ) ) );
//    c1->children().push_back( new TreeNode( root, QPoint( 5, 2 ) ) );
//    c1->children().push_back( new TreeNode( root, QPoint( 13, 4 ) ) );

//    c2->children().push_back( new TreeNode( root, QPoint( 12, 12 ) ) );
//    c2->children().push_back( new TreeNode( root, QPoint( 12, 5 ) ) );
//    c2->children().push_back( new TreeNode( root, QPoint( 51, 55 ) ) );
//    c2->children().push_back( new TreeNode( root, QPoint( 64, 34 ) ) );

    tv->setModel( model );
}

MainWindow::~MainWindow()
{
    delete ui;
}
