#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inputcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget *parent = 0, KeyboardConfig* kbd_confg = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
//    bool event( QEvent* e );
protected slots:
    void updateListView();

private:
    Ui::MainWindow *    ui;
    InputController*    input_controller_;
    KeyboardConfig*     kbd_confg_;
    InputListModel*     list_model_;
};

#endif // MAINWINDOW_H
