#include "inputlistmodel.h"
#include "keyboardconfig.h"

#include <QDebug>

InputListModel::InputListModel( QObject* parent )
    : QAbstractListModel( parent )
{}

void InputListModel::insertRecord( const QString& record ) {
    records_.push_front( record );
}

int InputListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED( parent )
    return records_.size();
}

int InputListModel::columnCount( const QModelIndex &parent ) const {
    Q_UNUSED( parent )
    return 1;
}

QVariant InputListModel::headerData(
    int                 section,
    Qt::Orientation     orientation,
    int                 role
) const {
    Q_UNUSED( section )
    Q_UNUSED( orientation )
    Q_UNUSED( role )

    return QVariant();
}

QVariant InputListModel::data( const QModelIndex &index, int role ) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    int pos = index.row();
    Records::const_iterator r_it = records_.begin();
    std::advance( r_it, pos );

    qDebug() << *r_it;

    return *r_it;
}

//void InputListModel::update() {
//    emit reset();
//}
