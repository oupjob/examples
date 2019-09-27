#ifndef INPUTLISTMODEL_H
#define INPUTLISTMODEL_H

#include <list>

#include <QAbstractListModel>
// #include "keyboardobserver.h"

#include "keyboardconfig.h"

class InputListModel : public QAbstractListModel
{
    Q_OBJECT
private:
    typedef std::list<QString>  Records;
    Records                     records_;

public:
    InputListModel( QObject* parent = 0 );
    void insertRecord( const QString& record );

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:
    void recordInserted();
};

#endif // INPUTLISTMODEL_H
