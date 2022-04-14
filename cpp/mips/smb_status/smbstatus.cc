#include <iostream>
#include <stdio.h>

using namespace std;

enum class SMB_ERROR : uint32_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    ERRDOS_INVALIDPARAM     = 0x00570001
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    ERRDOS_INVALIDPARAM     = 0x01005700
#endif
};

// #define prt(f, n) cout << #f " = " << bitset<n>(f) << endl;
// #define prt(f, n) std::cout << #f " = " << f << std::endl;
#define prt(n) printf("(%08x == ERRDOS_INVALIDPARAM) : %u\n", (n), (n) == static_cast<uint32_t>(SMB_ERROR::ERRDOS_INVALIDPARAM))

int main()
{
    uint8_t v[] = { 0x01, 0x00, 0x57, 0x00 };
    uint32_t* p = (uint32_t*)v;

    prt(*p);

    return 0;
}
