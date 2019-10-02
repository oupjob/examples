#include "StdAfx.h"
#include "data_structures.h"

using namespace System::IO;

// ***********************************************************
// ***********************************************************
// ����������� ������� ������ list_node
// ***********************************************************
// ***********************************************************

list_node::list_node() {	// ����������� �� ���������
	element_number_ = 0;
	circuit_number_ = 0; 
	contact_number_ = 0; 
	next_ = nullptr;
}

list_node::list_node( // ����������� � �������� ��������� ���������
	unsigned int	element_number, // ����� ��������
	unsigned int	circuit_number, // ����� ������������� ����
	unsigned int	contact_number // ����� ��������	
) {
	element_number_ = element_number; // ����� ��������
	circuit_number_ = circuit_number; // ����� ������������� ����
	contact_number_ = contact_number; // ����� ��������
	next_ = nullptr;
}

// ***********************************************************
// ***********************************************************
// ����������� ������� ������ list
// ***********************************************************
// ***********************************************************
void list::pushBack( list_node* node ) {
	if ( head_ == nullptr ) { // ������������� ������ ������, ���� ������ ����.
		head_ = node;
	} else {
		// ����� ��������� ������� � �������� � ��� node.
		list_node *n = head_;
		do {
			if ( n->next_ == nullptr ) {
				n->next_ = node;
				return;
			}
			n = n->next_;
		} while ( true );
	}
}

void list::pushFront( list_node* node ) {
	// �������� � ������
	node->next_ = head_;
	head_ = node;
}

void list::pushAfter( list_node* node, list_node* after ) {
	// �������� �����
	if ( node == nullptr || after == nullptr )
		return;

	node->next_ = after->next_;
	after->next_ = node;
}

void list::clear() {
	list_node* cur_node, *prev_node = head_;
	if ( head_ == nullptr ) 
		return;
	do {
		cur_node = prev_node->next_;
		delete prev_node;
		prev_node = cur_node;
	} while( cur_node != nullptr );
	head_ = nullptr;
}

unsigned int list::length() {
	unsigned int len = 0;
	for( list_node* n = head_; n != nullptr; n = n->next_ ) {
		len++;
	}
	return len;
}

// ***********************************************************
// ***********************************************************
// ����������� ������� ������ matrix_2d
// ***********************************************************
// ***********************************************************

matrix_2d::matrix_2d( unsigned int row_count, unsigned int column_count ) {
	row_count_ = row_count;		// ���������� �����������
	column_count_ = column_count;

	// �������������� ������ ����� �������
	matrix_ = new unsigned int*[ row_count_ ];
	// �������������� ���� ������ ������� � �����
	for( unsigned int i = 0; i < row_count_; i++ ) {
		matrix_[ i ] = new unsigned int[ column_count_ ];
	}
}

matrix_2d::~matrix_2d() {
	// �� �� �����, ��� � free, ����������
	for( unsigned int i = 0; i < row_count_; i++ ) {
		delete [] matrix_[ i ];
	}
	delete [] matrix_;
}

void matrix_2d::allocate( unsigned int row_count, unsigned int column_count ) {
	if ( matrix_ ) // ���� ������ ��� ���� �������� -- �������� �������
		free();
	// �������������� ������ ����� �������
	matrix_ = new unsigned int*[ row_count_ ];
	// �������������� ������ ������� � �����
	for( unsigned int i = 0; i < row_count_; i++ ) {
		matrix_[ i ] = new unsigned int[ column_count_ ];
	}
}

void matrix_2d::free() {
	// ������� �� ������ i-��� ������ ������� ...
	for( unsigned int i = 0; i < row_count_; i++ ) {
		if ( matrix_[ i ] ) 
			delete [] matrix_[ i ];	// ... ������� ������ ������
	}
	delete [] matrix_;	// ����� ������� ������ ���������� �� ������
	matrix_ = nullptr;	// ���������� ��������� � NULL
	row_count_ = column_count_ = 0;	// ���������� ����������� � 0 x 0
}

unsigned int matrix_2d::getElement( unsigned int i, unsigned int j ) {
	if ( i < row_count_ && j < column_count_ )
		return matrix_[ i ][ j ];
	return 0;
}

unsigned int matrix_2d::setElement( unsigned int i, unsigned int j, unsigned int value ) {
	if ( i < row_count_ && j < column_count_ ) {
		matrix_[ i ][ j ] = value;
		return value;
	}
	return 0;
}


/* ������� ����� � 
������ ������� ������������� ��������� �����, 
������� � ��������� ���������, 
�� ����������� ����� � �������� ��������� ������ �����, 
� ������� ������ ������� ������ ���������. */

// ��������� ����������� ������� ����� �� ������ ���������
int matrix_2d::setCircuitMatDimentionFromContactList( list* ls ) {
	// ��������� ������������ ����� ������ -- ������������ ����� ��������
	// ��������� ������������ ����� ������� -- ������������ ����� ��������
	free();
	const list_node* node = ls->getHead();
	do {
		if ( row_count_ < node->element_number_ ) 
			row_count_ = node->element_number_;
		if ( column_count_ < node->contact_number_ ) 
			column_count_ = node->contact_number_;
		node = node->next_;
	} while( node != nullptr );

	allocate( row_count_, column_count_ );
	return 0;
}

void matrix_2d::buildCircuitMatFromContactList( list* ls ) {
	setCircuitMatDimentionFromContactList( ls );
	// ����� ��� ������ ������� �������
	for( unsigned int i = 0; i < row_count_; i++ ) 
		for( unsigned int j = 0; j < column_count_; j++ ) 
			setElement( i, j, 0 );
	// ������� �� ������ �������� �������� �������
	const list_node* node = ls->getHead();
	do {
		setElement( 
			node->element_number_ - 1, 
			node->contact_number_ - 1,
			node->circuit_number_
		);
		node = node->next_;
	} while( node != nullptr );
}
/* 
������� ������������� � 
������ ������� ������������� �������� �����, 
������� � ������ (�����). 
�������� ��������� �������� 0, 1, -1 (� ������ ���������������� �����). 
	1  � ���� ������� ���������� ����� ��� ���� ������� �� �������, 
	-1 � ���� ������ � �������, 
	0  � � ��������� �������.

	������� V_i ������ ���������� ( � ����� ) ������� V_j ������ ����� 
	� ������ �����, ����� ����� ��� � ����� ����, �� �� � ����� ��������.
*/

int matrix_2d::setKoenigAdjacencyMatDimentionFromContactList( list* ls ) {
	free(); // ����������� ������ �� ��� �������
	
	// ����� ������
	//  ���������� ����� (���������) ����� ������������� ������ ��������
	//  ���������� �������� (�����) ����� ������������� ������ ����
	for( 
		const list_node* node_i = ls->getHead(); // i-�� �������
		node_i != nullptr;	//  ���� �� ��������� ����� ������ ...
		node_i = node_i->next_ // ... ���������� �� ������ �������� ����� ��������� �������
	) {
		// ����� ����������
		// ���� ����� �������� ������ ���������� �����, 
		//  �� ���������� ������������ ������ ������ ������ ��������
		if ( row_count_ < node_i->element_number_ )
			row_count_ = node_i->element_number_;

		// ���� ����� ���� ������ ���������� ��������, 
		//  �� ���������� ������������ ������� ������ ������ ����.
		if ( column_count_ < node_i->circuit_number_ )
			column_count_ = node_i->circuit_number_;
	}

	allocate( row_count_, column_count_ ); // �� ����������� ����������� �������� ��������� ������

	return 0;
}

void matrix_2d::buildiKoenigAdjacencyMatFromContactList( list* ls ) {
	setKoenigAdjacencyMatDimentionFromContactList( ls ); 
	// ����� ��� ������ ������� �������
	for( unsigned int i = 0; i < row_count_; i++ ) 
		for( unsigned int j = 0; j < column_count_; j++ ) 
			setElement( i, j, 0 );

	// ����� ������
	//  �� ������ ������� ������ ������� ����� �������� = i
	//  � ����� ���� = j
	//  ������ � �������� (i,j) ������������ �������� 1.
	for( 
		const list_node* node_i = ls->getHead();	// ������� �� ������ ������� 
		node_i != nullptr;	// ��������� ���� ������� �� ���� �������� ������
		node_i = node_i->next_ // ������������ �� ��������� �������
	) {
		setElement( node_i->element_number_ - 1, node_i->circuit_number_ - 1, 1 );
	}
}
