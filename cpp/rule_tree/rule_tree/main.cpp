#include <QCoreApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    TestRules test;
    test.buildAddRulesTree();
    test.print();

    return 0;
}
