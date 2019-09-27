#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <set>
#include <QObject>

#include "keyboardobserver.h"

class KeyboardConfig;
class InputListModel;

struct KeyboardObserverCmpLess {
    bool operator()( const KeyboardObserver& a, const KeyboardObserver& b ) const {
        return a.devPath() < b.devPath();
    }
};
typedef std::set<KeyboardObserver*> ObserverPtrSet;

class InputController : public QObject
{
    Q_OBJECT
private:
    ObserverPtrSet          observers_;
    const KeyboardConfig*   keyboard_cfg_;
    InputListModel*         list_model_;

public:
    InputController(
        QObject*                parent,
        const KeyboardConfig*   cfg,
        InputListModel*         list_model
    );
    virtual ~InputController();

signals:
    void    stop();
    void    inputHandled();
    void    errorHandled();

protected slots:
    virtual void    inputHandler( QString code2value );
    virtual void    errorHandler( QString msg );

public slots:
    virtual void    runObserve();
    virtual void    stopObserve();
};

#endif // INPUTCONTROLLER_H
