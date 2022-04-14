#include <iostream>
#include <iomanip>
#include <string>
#include <endian.h>

using namespace std;

template <typename RESULT_T, typename T> 
static RESULT_T compose_high_low(T high, T low, T (*letoh_func)(T) )
{
    RESULT_T res = letoh_func(high);
    res <<= sizeof(T) * 8;
    res |= letoh_func(low);
    return res;
}

#define TEST_16(h, l) \
uint16_t high = h, low = l; \
uint32_t n = compose_high_low<uint32_t>(high, low, le16toh); \
cout << hex << n << endl;


int main()
{
    TEST_16(1, 1);
    return 0;
}

