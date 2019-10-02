#ifndef TREENODE_H
#define TREENODE_H

#include <QAbstractItemModel>
#include <QRgb>
#include <QPoint>
#include <list>
#include <QDebug>

class TreeNode;

typedef std::list<TreeNode*> NodeList;

QString QPointToStr( const QPoint& point );

class TreeNode
{
    TreeNode*   parent_;
    QPoint      value_;
    QRgb        color_;
    NodeList    children_;

    void calculate( TreeNode* node );

public:
    TreeNode( TreeNode* parent, const QPoint& value );

    void    setValue( const QPoint& value ) { value_ = value; }
    const QPoint& getValue() { return value_; }

    TreeNode* childAt( int index );
    NodeList& children() { return  children_; }

    TreeNode* getParent() { return  parent_; }
    QRgb    getColor() { return color_; }

    void calcCentroid();
};

class TreeNodeModel : public QAbstractItemModel {
    TreeNode* root_;
public:
    void appendToRoot( TreeNode* node ) { root_->children().push_back( node ); }

    explicit TreeNodeModel( QObject *parent = 0 );
    ~TreeNodeModel();

    QModelIndex index( int row, int column, const QModelIndex& parent ) const;
    QModelIndex parent( const QModelIndex& child ) const;

    int rowCount    ( const QModelIndex &parent ) const;
    int columnCount ( const QModelIndex &parent ) const;

    QVariant data( const QModelIndex &index, int role ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    TreeNode* nodeFromIndex( const QModelIndex& index ) const ;

    TreeNode* const getRoot() { return root_; }
};

#endif // TREENODE_H
