#include "mainwindow.h"
#include <QApplication>

// #include "keyboardconfig.h";
#include "exception.h"
#include "inputcontroller.h"

#include <QMessageBox>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8" ) );

    QString cfg_file_name;
    if ( argc > 1 )
        cfg_file_name = argv[ 1 ];
    QApplication a( argc, argv );

    KeyboardConfig kbd_config;
    try {
        kbd_config.read( cfg_file_name );
    } catch ( Exception& e ) {
        QMessageBox mb;
        mb.setWindowTitle( QObject::tr( "Ошибка") );
        mb.setText( e.message() );

        mb.exec();
        return 1;
    }

    // qRegisterMetaType< std::pair<QString,QString> >( "std::pair<QString,QString>" );

    MainWindow w( 0, &kbd_config );
    w.show();

    return a.exec();
}
