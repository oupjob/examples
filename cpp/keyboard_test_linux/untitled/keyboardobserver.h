#ifndef KEYBOARDOBSERVER_H
#define KEYBOARDOBSERVER_H

#include <linux/input.h>

#include <map>
#include <QThread>
#include <QEvent>
#include <QTextStream>
#include <QFile>

#include "keyboardconfig.h"

#define BUFF_SZ_ 32

class KeyboardObserver : public QObject {
    Q_OBJECT
public:
    enum KbdType { K_QWERTY, K_FUNCTIONAL };

protected:
    QString         dev_path_;
    bool            do_listen_;
    QFile           file_;
    int             type_;

public:
    KeyboardObserver( QObject* parent, const QString& file, int type ) :
        QObject( parent ),
        dev_path_( file ),
        do_listen_( false ),
        type_( type )
    {}
    virtual ~KeyboardObserver() {}

    const QString& devPath() const { return dev_path_; }
    int type() { return type_; }
//    const input_event* getInputEvent() { return input_event_; }

public slots:
    virtual void process() {}
    virtual void stop() {}

signals:
    void input( QString code );
    void error( QString text );
};

class QwertyKeyboardObserver : public KeyboardObserver {
    Q_OBJECT

protected:
    input_event*    input_event_;

public:
    QwertyKeyboardObserver( QObject* parent, const QString& file ) :
        KeyboardObserver( parent, file, KeyboardObserver::K_QWERTY ),
        input_event_( new input_event() )
    {}
    ~QwertyKeyboardObserver() { if ( input_event_ ) delete input_event_; }

    const QString& devPath() const { return dev_path_; }
//    const input_event*  getInputEvent() { return input_event_; }

public slots:
    virtual void process();
    virtual void stop();
};

class  FunctionalKeyboardObserver : public KeyboardObserver {
    Q_OBJECT

public:
    FunctionalKeyboardObserver( QObject* parent, const QString& file ) :
        KeyboardObserver( parent, file, KeyboardObserver::K_FUNCTIONAL )
    {}
    ~FunctionalKeyboardObserver() {}

    const QString& devPath() const { return dev_path_; }
//    const input_event* getInputEvent() { return input_event_; }

public slots:
    virtual void process();
    virtual void stop();
};

#endif // KEYBOARDOBSERVER_H
