#include <iostream>
#include <iomanip>

using namespace std;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const uint16_t PRI_FACILTY_MASK = 0xFFF8;
static const uint16_t PRI_SEVERITY_MASK = 0x0007;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static const uint16_t PRI_FACILTY_MASK = 0xFFF8;
static const uint16_t PRI_SEVERITY_MASK = 0x0007;
#else
#error "Unspecified host byte order, please fix 'smb1.proto'"
#endif

int main()
{
    uint16_t pri = 135;

    cout << "PRI_FACILTY_MASK = " << PRI_FACILTY_MASK << ", PRI_SEVERITY_MASK = " << PRI_SEVERITY_MASK << endl; 
    cout << hex << "facilty = 0x" << ((pri & PRI_FACILTY_MASK) >> 3) << ", severity = 0x" << (pri & PRI_SEVERITY_MASK) << endl;
    return 0;
};
