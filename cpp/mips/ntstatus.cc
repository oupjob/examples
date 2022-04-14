#include <iostream>
#include <stdio.h>

using namespace std;

struct nt_status_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint32_t        code_pt2:8;
    uint32_t        code_pt1:8;

    uint32_t        facilty_pt2:8;
    uint32_t        facilty_pt1:4;

    uint32_t        n_bit:1;
    uint32_t        c_bit:1;
    uint32_t        sev:2;  // SEVERITY

    uint16_t facilty() const { return (facilty_pt1 << 8) + facilty_pt2; }
    uint16_t code() const { return (code_pt1 << 8) + code_pt2; }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint32_t        code_pt2:8;
    uint32_t        code_pt1:8;

    uint32_t        facilty_pt2:8;

    uint32_t        sev:2;  // SEVERITY
    uint32_t        c_bit:1;
    uint32_t        n_bit:1;
    uint32_t        facilty_pt1:4;
    
    uint16_t facilty() const { return (facilty_pt1 << 8) + facilty_pt2; }
    uint16_t code() const { return (code_pt1 << 8) + code_pt2; }
#else 
#error "Unspecified host byte order, please fix 'A'"
#endif
};

typedef nt_status_t A;

// #define prt(f, n) cout << #f " = " << bitset<n>(f) << endl;
// #define prt(f, n) std::cout << #f " = " << f << std::endl;
#define prt(f, n) printf(#f " = %08x\n", f)

int main()
{
    uint8_t v[] = { 0b00000001, 0b00000001, 0b11111111, 0b11100001 };
    A* p = (A*)v;

    prt(p->sev, 2);
    prt(p->c_bit, 1);
    prt(p->n_bit, 1);
    prt(p->facilty_pt1, 4);
    prt(p->facilty_pt2, 1);
    prt(p->code_pt1, 8);
    prt(p->code_pt2, 8);

    prt(p->code(), 16);
    prt(p->facilty(), 16);

    return 0;
}
