#include <QDebug>

#include "inputcontroller.h"
#include "inputlistmodel.h"
#include "exception.h"

InputController::InputController(
    QObject*                parent,
    const KeyboardConfig*   cfg,
    InputListModel*         input_list_model
) :
    QObject( parent ), keyboard_cfg_( cfg ), list_model_( input_list_model )
{
    connect( parent, SIGNAL( destroyed() ), this, SLOT( stopObserve() ) );
}

InputController::~InputController() {
    stopObserve();
}

void InputController::runObserve() {
    KeyboardInfoMap::const_iterator kbd_it = keyboard_cfg_->kbd_info_map_.begin();

    for(; kbd_it != keyboard_cfg_->kbd_info_map_.end(); ++kbd_it ) {
        KeyboardObserver* observer = 0;
        if ( kbd_it->first.type == KbdDescription::K_QWERTY )
            observer = new QwertyKeyboardObserver(
                0, kbd_it->first.dev_name
            );
        else if ( kbd_it->first.type == KbdDescription::K_FUNCTIONAL )
            observer = new FunctionalKeyboardObserver(
                0, kbd_it->first.dev_name
            );
        else continue;

        observers_.insert( observer );

        QThread* thread = new QThread( this );

        connect(
            thread,     SIGNAL( started() ),
            observer,   SLOT(   process() )
        );
        connect(
            this,       SIGNAL( stop() ),
            observer,   SLOT(   stop() )
        );
        connect(
            thread,     SIGNAL( destroyed() ),
            observer,   SLOT(   stop() )
        );
        connect(
            observer,   SIGNAL( input(QString) ),
            this,       SLOT(   inputHandler(QString) )
        );
        connect(
            observer,   SIGNAL( error(QString) ),
            this,       SLOT(   errorHandler(QString) )
        );

        observer->moveToThread( thread );
        thread->start();
    }
}

void InputController::stopObserve() {
    emit stop();
    ObserverPtrSet::const_iterator os_it = observers_.begin();
    for(; os_it != observers_.end(); ++os_it ) {
        if ( ( *os_it )->thread() ) {
            ( *os_it )->thread()->exit( 0 );
        }
        delete *os_it;
    }
}

void InputController::inputHandler( QString code ) {
    KeyboardObserver* kbd_observer =
        static_cast<KeyboardObserver*>( sender() );
    QString record, rec( "%1 - %2" );
    if ( kbd_observer->type() == KbdDescription::K_QWERTY ) {
        Code2Key code2key = keyboard_cfg_->getCode2Key( kbd_observer->devPath(), code );
        if ( code2key.first.isEmpty() ) return;
        record = rec.arg( code2key.first ).arg( code2key.second );

    } else if ( kbd_observer->type() == KbdDescription::K_FUNCTIONAL )
        record = rec.arg( code, ( tr( "ф.к. " ) + code ) );

    qDebug() << record;

    list_model_->insertRecord( record );
    emit inputHandled();
}

void InputController::errorHandler( QString  msg ) {
    emit errorHandled();
    throw Exception( msg );
}
