#include <iostream>

using namespace std;

int main()
{
    uint16_t n = 0x01FF;
    uint8_t* p = (uint8_t*)&n;
    cout << "Hello, MIPS! Endiannes is: " << ((*p == 0x01) ? "BE" : "LE") << endl;
    return 0;
}
