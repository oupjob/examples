#pragma once
#include <vcclr.h>
// Структура элемента односвязного списка входных данных.
// Описывает один контакт, и принадлежность его элементу и цепи.

struct list_node {
	unsigned int	element_number_; // Номер элемента
	unsigned int	circuit_number_; // Номер электрической цепи
	unsigned int	contact_number_; // Номер контакта

	list_node*	next_;		// Указатель на следующую вершину списка

	list_node(); // Конструктор по умолчанию
	list_node( // Конструктор с заданием элементов структуры
		unsigned int	element_number, // Номер элемента
		unsigned int	circuit_number, // Номер электрической цепи
		unsigned int	contact_number // Номер контакта	
	);
};

// Класс списка элементов входных данных (контактов)
class list { 
private:
	list_node*	head_;	// Первый элемент (голова) списка.

public:
	list() { // конструктор
		head_ = nullptr;
	}
	~list() { clear(); } // Деструктор

	void	pushBack( list_node* node ); // Добавить node в конец списка
	void	pushFront( list_node* node ); // Добавить node в начало списка
	void	pushAfter( list_node* node, list_node* after ); // добавить вершину node после вершины after
	void	clear(); // Очистить список

	const list_node* getHead() { return head_; }

	// длина списка
	unsigned int length();

};

class matrix_2d {
private:
	unsigned int**	matrix_;		// Динамический двумерный массив хранящий матрицу
	unsigned int	row_count_;		// количество строк матрицы
	unsigned int	column_count_;	// количество столбцов матрицы

public:
	matrix_2d() {  // Конструктор без параметров (конструктор по умолчанию)
		matrix_ = nullptr;
		row_count_ = column_count_ = 0;
	}
	matrix_2d( unsigned int row_count, unsigned int column_count ); // Конструктор с выделением памяти
	~matrix_2d();

public:
	// собрать матрицу из списка контактов
	void buildCircuitMatFromContactList( list* ls ); // матрицу цепей
	void buildiKoenigAdjacencyMatFromContactList( list* ls ); // матрицу инцидентности
private:
	// вычисление размерности на основе элементов списка контактов.
	int setCircuitMatDimentionFromContactList( list* ls ); // матрица цепей
	int setKoenigAdjacencyMatDimentionFromContactList( list* ls ); // матрица инцидентности

public:
	// Доступ к элементу на пересечении строки i и столбца j,
	unsigned int getElement( unsigned int i, unsigned int j );
	// Выставить значение элемента на пересечении строки i и столбца j в value
	unsigned int setElement( unsigned int i, unsigned int j, unsigned int value );

	unsigned int getRowCount() { return row_count_; }
	unsigned int getColumnCount() { return column_count_; }

	// Выделить память под матрицу
	void allocate( unsigned int row_count, unsigned int column_count );
	// Осовободить память
	void free();
};