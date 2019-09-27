#include <QDebug>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

#include "keyboardobserver.h"
#include "exception.h"
#include "keyboardconfig.h"

void QwertyKeyboardObserver::process() {
    char* dev_path = dev_path_.toAscii().data();
    int kbd_fd = open( dev_path, O_RDONLY | O_NONBLOCK );

    if ( kbd_fd == -1 ) {
        emit error( E_OPEN_KBD_DEV_FILE( dev_path_ ) );
        return;
    }

    do_listen_ = true;
    while ( do_listen_ ) {
        int bytes = read( kbd_fd, input_event_, sizeof( *input_event_ ) );
        Q_UNUSED( bytes )

        if ( input_event_->type == EV_KEY ) {
            if ( input_event_->value != 1 ) continue;
            QString code( "%1" );
            code = code.arg( input_event_->code );
            emit input( code );

//            qDebug() << "code = " << input_event_->code
//                     << " value = " << input_event_->value;
        }
    }
}

void QwertyKeyboardObserver::stop() {
    do_listen_ = false;
}
