#include <iostream>
#include <memory>
#include <vector>

#include "sharedptr.h"

using namespace std;

void printSPTable( const std::string& header = "shared pointers table dump: " ) {
    SharedPtrTable::Table::iterator t_it = SharedPtrTable::begin();

    cout << endl << header << endl;
    for(; t_it != SharedPtrTable::end(); ++t_it ) {
        cout << " ptr= " << t_it->ptr
             << " count = " << t_it->count
             << endl;
    }
}

typedef vector<int> IntVec;

SharedPtr<IntVec> test() {
    const SharedPtrTable::Table& t = SharedPtrTable::table();
    SharedPtr<IntVec>
    p1 = new IntVec,
    p2 = 0, p3 = p2;

    cout << "function: test()" << endl;
    printSPTable( "(p1):" );
    p2 = p1;
    printSPTable( "(p1,p2):" );
    p3 = p2;
    printSPTable( "(p1,p2,p3):" );

    p3 = 0;
    printSPTable( "(p1,p2):" );

    p3 = new IntVec;
    printSPTable( "(p1,p2), (p3):" );

    p3 = 0;
    printSPTable( "(p1,p2):" );

    p2 = p3;
    printSPTable( "(p1), (p2,p3) = 0:" );


    cout << "end of test()" << endl;
    return p1;
}

int main()
{
    SharedPtr<IntVec> p = test();
    printSPTable();

    cout << "press any key to exit..." << endl;
    return 0;
}

