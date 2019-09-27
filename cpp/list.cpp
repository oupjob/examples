#include <iostream>
#include <iomanip>
using namespace std;
 
struct List{
    int info;
    List *pred, *next;
};
 
// Функция вставляет элемент p в двусвзный список посел элмента last 
// и возвращает адрес вставленного элемента
List * InsertElementInList(List * last, List * p)
{
    if(last && p)
    {
        p->pred = last;
        p->next = last->next;
        last->next = p;
        p->next->pred = p;
        return p;
    }
    else
        return NULL;
}
 
 
 
//Функция создает двусвязный список с двумя сторожами head and tail
// по входной поледовательности целых чисел, вводимх с консоли до нуля
void CreateList(List *&head, List *&tail)
{
    head = new List;
    tail = new List;
    head->next = tail;
    tail->pred = head;
    int k;
    cout << "Input numbers (0  end)" << endl;
    cin >> k;
    List * last = head;
    while(k)
    {
        List * p = new List;
        p->info = k;
        last = InsertElementInList(last, p);
        cin >> k;
    }
    return;
}
 
// Функция выводит на консоль первернутый двусвзный список
void ReverseList(List *& head, List *& tail)
{
    List * p = head->next, * tmp;
    while(p != tail)
    {
		cout << "cur = " << p->info << endl;
        tmp = p->next;
        p->next = p->pred;
        p->pred = tmp;
        p = tmp;
    }

    tmp = head->next;
    head->next = tail->pred;
    tail->pred = tmp;
	tail->next = head->pred = NULL;
	tmp = head;
	head = tail;
	tail = tmp;
}
 
// Фунция выводит на консоь двусвзяный список со сторожами head and tail 
void PrintList(List * head, List * tail)
{
    List * p = head->next;
    while(p != tail)
    {
        cout << setw(6) << p->info << endl;
        p = p->next;
    }
    cout << endl;
    return;
}
 
 
int main()
{
    List *head, *tail = NULL;
    CreateList(head, tail);
    cout << "Source list:" << endl;
    PrintList(head, tail);
    cout << "Reversed list:" << endl;
    ReverseList(head, tail);
    PrintList(head, tail);
}
