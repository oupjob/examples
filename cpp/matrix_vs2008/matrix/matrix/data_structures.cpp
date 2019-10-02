#include "StdAfx.h"
#include "data_structures.h"

using namespace System::IO;

// ***********************************************************
// ***********************************************************
// Определение методлв класса list_node
// ***********************************************************
// ***********************************************************

list_node::list_node() {	// Конструктор по умолчанию
	element_number_ = 0;
	circuit_number_ = 0; 
	contact_number_ = 0; 
	next_ = nullptr;
}

list_node::list_node( // Конструктор с заданием элементов структуры
	unsigned int	element_number, // Номер элемента
	unsigned int	circuit_number, // Номер электрической цепи
	unsigned int	contact_number // Номер контакта	
) {
	element_number_ = element_number; // Номер элемента
	circuit_number_ = circuit_number; // Номер электрической цепи
	contact_number_ = contact_number; // Номер контакта
	next_ = nullptr;
}

// ***********************************************************
// ***********************************************************
// Определение методлв класса list
// ***********************************************************
// ***********************************************************
void list::pushBack( list_node* node ) {
	if ( head_ == nullptr ) { // устанавливаем голову списка, если список пуст.
		head_ = node;
	} else {
		// Найти последнюю вершину и добавить в нее node.
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
	// Добавить в начало
	node->next_ = head_;
	head_ = node;
}

void list::pushAfter( list_node* node, list_node* after ) {
	// Добавить после
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
// Определение методлв класса matrix_2d
// ***********************************************************
// ***********************************************************

matrix_2d::matrix_2d( unsigned int row_count, unsigned int column_count ) {
	row_count_ = row_count;		// выставляем размерность
	column_count_ = column_count;

	// инициализируем массив строк матрицы
	matrix_ = new unsigned int*[ row_count_ ];
	// инициализируем сами строки матрицы в цикле
	for( unsigned int i = 0; i < row_count_; i++ ) {
		matrix_[ i ] = new unsigned int[ column_count_ ];
	}
}

matrix_2d::~matrix_2d() {
	// то же самое, что и free, деструктор
	for( unsigned int i = 0; i < row_count_; i++ ) {
		delete [] matrix_[ i ];
	}
	delete [] matrix_;
}

void matrix_2d::allocate( unsigned int row_count, unsigned int column_count ) {
	if ( matrix_ ) // Если память уже была выделена -- очистить матрицу
		free();
	// инициализируем массив строк матрицы
	matrix_ = new unsigned int*[ row_count_ ];
	// инициализируем строки матрицы в цикле
	for( unsigned int i = 0; i < row_count_; i++ ) {
		matrix_[ i ] = new unsigned int[ column_count_ ];
	}
}

void matrix_2d::free() {
	// проходя по каждой i-той строке матрицы ...
	for( unsigned int i = 0; i < row_count_; i++ ) {
		if ( matrix_[ i ] ) 
			delete [] matrix_[ i ];	// ... удаляем каждую строку
	}
	delete [] matrix_;	// затем удаляем массив указателей на строки
	matrix_ = nullptr;	// выставляем указатель в NULL
	row_count_ = column_count_ = 0;	// выставляем размерность в 0 x 0
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


/* Матрица цепей – 
строки матрицы соответствуют элементам схемы, 
столбцы – контактам элементов, 
на пересечении строк и столбцов находятся номера цепей, 
в которые входит элемент данным контактом. */

// Вычислить размерность матрицы цепей по списку контактов
int matrix_2d::setCircuitMatDimentionFromContactList( list* ls ) {
	// Вычисляем максимальный номер строки -- максимальный номер элемента
	// Вычисляем максимальный номер столбца -- максимальный номер контакта
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
	// Здесь для начала занулим матрицу
	for( unsigned int i = 0; i < row_count_; i++ ) 
		for( unsigned int j = 0; j < column_count_; j++ ) 
			setElement( i, j, 0 );
	// проходя по списку выставим элементы матрицы
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
Матрица инцидентности – 
строки матрицы соответствуют вершинам графа, 
столбцы – ребрам (дугам). 
Элементы принимают значения 0, 1, -1 (в случае ориентированного графа). 
	1  – если вершина инцидентна ребру или дуга выходит из вершины, 
	-1 – дуга входит в вершину, 
	0  – в остальных случаях.

	Вершина V_i списка инцидентна ( в графе ) вершине V_j списка тогда 
	и только тогда, когда когда они в одной цепи, но не в одном элементе.
*/

int matrix_2d::setIncidenceMatDimentionFromContactList( list* ls ) {
	free(); // Освобождаем память из под матрицы
	
	// Обход списка, для каждой вершины будут просматриваться следующие после нее
	// Количество строк (вершин графа) равно количеству элементов
	// Количастов столбцов (ребер графа) определяется исходя из того,
	//  суммой количеств ребер в каждом полном графе описывающим цепи по отдельности от остальных
	// Вершины с равными номерами элементов не просматриваются
	// Так как цепь не замыкается на элементе.
	for( 
		const list_node* node_i = ls->getHead(); // i-ая вершина
		node_i != nullptr;	//  пока не достигнем конца списка ...
		node_i = node_i->next_ // ... выставляем на каждой итерации цикла следующую вершину
	) {
		if ( row_count_ < node_i->element_number_ )
			row_count_ = node_i->element_number_;
		
		// Обход по последующим вершинам цикл в цикле
		for( 
			const list_node* node_j = node_i; // начиная от i-той вершины 
			node_j != nullptr;	//  пока не достигнем конца списка ...
			node_j = node_j->next_	// ... выставляем на каждой итерации цикла следующую вершину V_j
		) {
			// Не принимаем в расчет вершины принадлежащие одному и тому же элементу
			if ( node_i->element_number_ == node_j->element_number_ )
				continue;
			// Если номера элементов разные
			// Но номера цепей совпадут, то увеличиваем количество дуг
			// количество дуг эквивалентно количеству столбцов в матрице инцидентности.
			if ( node_i->circuit_number_ == node_j->circuit_number_ )
				column_count_++;
		}
	}

	allocate( row_count_, column_count_ ); // по расчитанным показателям выделяем двумерный массив

	return 0;
}

void matrix_2d::buildiIncidenceMatFromContactList( list* ls ) {
	setIncidenceMatDimentionFromContactList( ls );
	unsigned int edge_number;
	// Здесь для начала занулим матрицу
	for( unsigned int i = 0; i < row_count_; i++ ) 
		for( unsigned int j = 0; j < column_count_; j++ ) 
			setElement( i, j, 0 );

	// Обход списка, для каждой вершины будут просматриваться последующие после нее
	// Вершины (элементы) с равными номерами цепей будут соединены дугой
	// Вершины с равными номерами элементов не просматриваются
	// Так как цепь не замыкается на элементе.
	for( 
		const list_node* node_i = ls->getHead();	// начиная от первой вершины 
		node_i != nullptr;	// запускаем цикл прохода по всем вершинам списка
		node_i = node_i->next_ // переключение на следующую вершину
	) {
		// Обход остальных вершин, начиная с текущей
		for( 
			const list_node* node_j = node_i; // Начиная от вершины node_i ...
			node_j != nullptr;	// .. обходим остальные вершины списка 
			node_j = node_j->next_ // переключение на следующую вершину
		) {
			// Если вершины принадлежат одному и тому же элементу -- переход на следующую итерацию.
			if ( node_i->element_number_ == node_j->element_number_ )
				continue;

			// Если номера цепей вершины совпали -- то соединеям их дугой ...
			// ... устанавливаем в матрице числа 1 в текущей дуге (столбце)
			// и строках соответствующим их (контактов) элементам.
			if ( node_i->circuit_number_ == node_j->circuit_number_ ) {
				setElement( node_i->element_number_ - 1, edge_number, 1 );
				setElement( node_j->element_number_ - 1, edge_number, 1 );
				edge_number++; // Переходим к следующей дуге.
			}
		}
	}
}
