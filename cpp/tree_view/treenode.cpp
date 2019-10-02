#include "treenode.h"
#include <QDebug>
#include <QPixmap>

TreeNode::TreeNode( TreeNode* parent, const QPoint& value )
    : value_(value), color_(qrand()), parent_(parent)
{
}

TreeNode* TreeNode::childAt(int index) {
    NodeList::iterator it  = children_.begin();
    std::advance( it, index );

    if ( it != children().end() ) return *it;
    return 0;
}

// ____________________________________________________________________________________________________

TreeNodeModel::TreeNodeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    root_ = new TreeNode( 0, QPoint( 0, 0 ) );
//    beginInsertRows();
//    insertRow( 0, createIndex( 1, 0, root_) );
//    endInsertRows();
}

TreeNodeModel::~TreeNodeModel() {
    if ( root_ ) delete root_;
}

TreeNode* TreeNodeModel::nodeFromIndex( const QModelIndex &index ) const {
    if ( index.isValid() )
        return static_cast<TreeNode*>( index.internalPointer() );
    return root_;
}

QModelIndex TreeNodeModel::index( int row, int column, const QModelIndex& parent ) const {
    qDebug() << "CTM - index: parent index = " << parent;
    if ( !hasIndex( row, column, parent ) ) return QModelIndex();
    qDebug() << "has index! ";

    TreeNode* parent_node = nodeFromIndex( parent );
    if ( !parent_node ) return QModelIndex();

    qDebug() << "parent TreeNode: " << parent_node->getValue();

    if ( parent_node->children().size() >= row ) return QModelIndex();
    TreeNode* child_node  = parent_node->childAt( row );
    qDebug() << "child  TreeNode: " << child_node->getValue();

    return createIndex( row, column, child_node );
}

QModelIndex TreeNodeModel::parent( const QModelIndex& child ) const {
    qDebug() << "CTM - parent: child_index = " << child;
    TreeNode* node = nodeFromIndex( child );
    if ( !node ) {
        qDebug() << "CTM - parent: !TreeNode";
        return   QModelIndex();
    }

    TreeNode* parent = node->getParent();
    if ( !parent ) {
        qDebug() << "CTM - parent: !parent";
        return createIndex( 0, 0, root_ );
    }

    TreeNode* grand_parent = parent->getParent();
    if ( !grand_parent ) {
        qDebug() << "CTM - parent: !grand_parent";
        NodeList::iterator it = root_->children().begin();
        for (int i = 0; it != root_->children().end(); ++it )
            if ( *it  ==  parent) return createIndex( i, child.column(), parent );
        return QModelIndex();
    }

    NodeList::iterator it = root_->children().begin();
    for (int i = 0; it != root_->children().end(); ++it )
        if ( *it  ==  parent) {
            qDebug() << "CTM - parent: " << nodeFromIndex( child )->getValue();
            if ( *it  ==  parent) return createIndex( i, child.column(), parent );
        }

    return QModelIndex();
}

QVariant TreeNodeModel::data( const QModelIndex &index, int role ) const {
    qDebug() << "CTM data:";
    if ( !index.isValid() )  {
        qDebug() << "CTM data: invalid index." ;
        return QVariant();
    }

    qDebug() << "CTM data:  column  = " << index.column()
             << "           row     = " << index.row()
             << " TreeNode: " << nodeFromIndex( index )->getValue();

    if ( index.column() == 0 && role == Qt::DecorationRole ) { // create pixmap and fill color
        QColor color( nodeFromIndex( index )->getColor() );
        QPixmap pixmap( 20, 20 );
        pixmap.fill( color );
        return pixmap;
    }

    if ( index.column() == 1 && role == Qt::DisplayRole ) {
        return QPointToStr( nodeFromIndex( index )->getValue() );
    }
}

QVariant TreeNodeModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    qDebug() << "headerData: " << section;
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole ) {
        if ( section == 0 )
            return tr( "Color" );
        else if ( section == 1 )
            return tr( "Name" );
        return QVariant();
    }
    return QVariant();
}

int TreeNodeModel::rowCount( const QModelIndex &parent ) const {
//    if ( parent.column() > 0 )  return 0;

    qDebug() << "CTM rowCount: ";
    TreeNode* parent_node;
    if ( ! parent.isValid() ) return 0;
    parent_node = nodeFromIndex( parent );
    qDebug() << "CTM rowCount: parent_node: " << parent_node->getValue();

    return parent_node->children().size();
}

int TreeNodeModel::columnCount( const QModelIndex &parent ) const {
//    qDebug() << "columntCount:  count = 0 ";
//    if ( parent.isValid() && parent.column() != 0  ) return 0;
    return 2;
}

Qt::ItemFlags TreeNodeModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags item_flags = QAbstractItemModel::flags( index );

    if ( index.isValid() ) {
        item_flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;

        if ( index.column() == 1 ) {
            item_flags |= Qt::ItemIsUserCheckable;
        }
    }
}


QString QPointToStr( const QPoint& point ) {
    QString     string;
    QDebug      stream( &string );

    stream << point;

    return string;
}
