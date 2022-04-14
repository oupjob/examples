#include <iostream>
#include <stdio.h>

using namespace std;

struct capabilities_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint16_t        reserved1:3;
    uint16_t        dfs:1;
    uint16_t        continuous_availability:1;
    uint16_t        scaleout:1;
    uint16_t        cluster:1;
    uint16_t        assymetric:1;

    uint16_t        redirect_to_owner:1;
    uint16_t        reserved2:7;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint16_t        assymetric:1;
    uint16_t        cluster:1;
    uint16_t        scaleout:1;
    uint16_t        continuous_availability:1;
    uint16_t        dfs:1;
    uint16_t        reserved1:3;
    
    uint16_t        reserved2:7;
    uint16_t        redirect_to_owner:1;
#else 
#error "Unspecified host byte order, please fix 'A'"
#endif
};

typedef capabilities_t A;

// #define prt(f, n) cout << #f " = " << bitset<n>(f) << endl;
// #define prt(f, n) std::cout << #f " = " << f << std::endl;
#define prt(f, n) printf(#f " = %08x\n", f)

int main()
{
    uint8_t v[] = { 0b00101011, 0b10001001 };
    A* p = (A*)v;

    prt(p->reserved1, 3);
    prt(p->dfs, 1);
    prt(p->continuous_availability, 1);
    prt(p->scaleout, 1);
    prt(p->cluster, 1);
    prt(p->assymetric, 1);
    
    prt(p->redirect_to_owner, 1);
    prt(p->reserved2, 7);

    return 0;
}
