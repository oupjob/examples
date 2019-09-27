#include <QDebug>
#include <QTextStream>

#include <fcntl.h>
#include <unistd.h>

#include "keyboardobserver.h"
#include "exception.h"
#include "keyboardconfig.h"
#include "fkbd_structs.h"

void FunctionalKeyboardObserver::process() {
    fkbd_timeval last_fkbd_ev_time = { 0, 0 };
    char* dev_path = dev_path_.toAscii().data();

    QString symbols;

    fkbd_symbol_event fkbd_sym_ev;
    QTextStream os( &symbols );
    qDebug() << "FunctionalKeyboardObserver: open " << dev_path;

    int fd = open( dev_path, O_RDONLY );
    if ( fd == -1 ) {
        emit error( E_CANNOT_OPEN_FILE( dev_path_ ) );
    }

    qDebug() << "FunctionalKeyboardObserver: fd = " << fd;

    do_listen_ = true;
    while( do_listen_ ) {
        qDebug() << "FunctionalKeyboardObserver: fd = " << fd;

        int bytes = read( fd, &fkbd_sym_ev, sizeof( fkbd_sym_ev ) );
        qDebug() << "FunctionalKeyboardObserver: bytes = " << bytes;
        if ( !bytes ) continue;

        qDebug() << "FunctionalKeyboardObserver: readed"
                 << "type = " << fkbd_sym_ev.event_type.type;
        if ( fkbd_sym_ev.event_type.type != 1 ) continue;

        __u64 code = fkbd_sym_ev.event_code.code;
        if ( code <= 11 ) {
            if ( code == 11 ) code = 0;
            else --code;
            os << code;
        } else if ( code == 28 ){
            os << " ";
            emit input( symbols );
            symbols.clear();
        } else
            os << code;

        qDebug() << "FunctionalKeyboardObserver: code = " << code;

        last_fkbd_ev_time = fkbd_sym_ev.event_end.time;
    }
}

void FunctionalKeyboardObserver::stop() {
    do_listen_ = false;
}
