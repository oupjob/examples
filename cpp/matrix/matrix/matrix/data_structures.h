#pragma once
#include <vcclr.h>
// ��������� �������� ������������ ������ ������� ������.
// ��������� ���� �������, � �������������� ��� �������� � ����.

struct list_node {
	unsigned int	element_number_; // ����� ��������
	unsigned int	circuit_number_; // ����� ������������� ����
	unsigned int	contact_number_; // ����� ��������

	list_node*	next_;		// ��������� �� ��������� ������� ������

	list_node(); // ����������� �� ���������
	list_node( // ����������� � �������� ��������� ���������
		unsigned int	element_number, // ����� ��������
		unsigned int	circuit_number, // ����� ������������� ����
		unsigned int	contact_number // ����� ��������	
	);
};

// ����� ������ ��������� ������� ������ (���������)
class list { 
private:
	list_node*	head_;	// ������ ������� (������) ������.

public:
	list() { // �����������
		head_ = nullptr;
	}
	~list() { clear(); } // ����������

	void	pushBack( list_node* node ); // �������� node � ����� ������
	void	pushFront( list_node* node ); // �������� node � ������ ������
	void	pushAfter( list_node* node, list_node* after ); // �������� ������� node ����� ������� after
	void	clear(); // �������� ������

	const list_node* getHead() { return head_; }

	// ����� ������
	unsigned int length();

};

class matrix_2d {
private:
	unsigned int**	matrix_;		// ������������ ��������� ������ �������� �������
	unsigned int	row_count_;		// ���������� ����� �������
	unsigned int	column_count_;	// ���������� �������� �������

public:
	matrix_2d() {  // ����������� ��� ���������� (����������� �� ���������)
		matrix_ = nullptr;
		row_count_ = column_count_ = 0;
	}
	matrix_2d( unsigned int row_count, unsigned int column_count ); // ����������� � ���������� ������
	~matrix_2d();

public:
	// ������� ������� �� ������ ���������
	void buildCircuitMatFromContactList( list* ls ); // ������� �����
	void buildiKoenigAdjacencyMatFromContactList( list* ls ); // ������� �������������
private:
	// ���������� ����������� �� ������ ��������� ������ ���������.
	int setCircuitMatDimentionFromContactList( list* ls ); // ������� �����
	int setKoenigAdjacencyMatDimentionFromContactList( list* ls ); // ������� �������������

public:
	// ������ � �������� �� ����������� ������ i � ������� j,
	unsigned int getElement( unsigned int i, unsigned int j );
	// ��������� �������� �������� �� ����������� ������ i � ������� j � value
	unsigned int setElement( unsigned int i, unsigned int j, unsigned int value );

	unsigned int getRowCount() { return row_count_; }
	unsigned int getColumnCount() { return column_count_; }

	// �������� ������ ��� �������
	void allocate( unsigned int row_count, unsigned int column_count );
	// ����������� ������
	void free();
};