#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <bitset>
#include <algorithm>

using namespace std;

template <typename T>
T invert_bytes(T bytes)
{
    uint8_t *p = reinterpret_cast<uint8_t*>(&bytes),
            *p_end =  p + sizeof(bytes) - 1;
    for(; p < p_end; ++p, --p_end)
    {
        *p = *p ^ *p_end;
        *p_end = *p ^ *p_end;
        *p = *p ^ *p_end;
    }
    
    return bytes;
}

#define LEN_BITS sizeof(T) * 8

// Последовательный доступ к битам как в массиве 
template <typename T, typename OUT_T = uint8_t> 
OUT_T extract_bits_to_le(T bits, uint8_t pos, uint8_t end)
{
//    uint8_t pos_be_octet_end = (uint8_t(pos / 8) + 1) * 8 - 1; // Индекс последнего бита в октете (15 если pos = 10)
//    uint8_t pos_be_octet_beg = pos_be_octet_end - 7;    // Индекс первого бита в октете (8 если pos = 10)
//    uint8_t pos_be = pos_be_octet_beg + (pos_be_octet_end - pos); // Позиция бита в октете в x86 представлении
//    
//    uint8_t end_be_octet_end = (uint8_t(end / 8) + 1) * 8 - 1;
//    uint8_t end_be_octet_beg = end_be_octet_end - 7;
//    uint8_t end_be = end_be_octet_beg + (end_be_octet_end - end);

//    cout << "pos = " << (uint16_t(pos) & 0xff) << ", pos_be = " << (uint16_t(pos_be) & 0xff) << ", " 
//         << "end = " << (uint16_t(end) & 0xff) << ", end_be = " << (uint16_t(end_be) & 0xff)
//         << endl;

    cout << "pos = " << (uint16_t(pos) & 0xff) << ", " 
         << "end = " << (uint16_t(end) & 0xff)
         << endl;

    cout << "                   1111111111222222222233" << endl;
    cout << "         01234567890123456789012345678901" << endl;  
    cout << " bits0 = " << bitset<LEN_BITS>(bits) << " <<" << endl;    
//    bits = invert_bytes(bits);
//    cout << " bits1 = " << bitset<LEN_BITS>(bits) << " >>" << endl;    
    bits <<= pos; // sizeof(T) * 8 - end - 1;
    cout << " bits2 = " << bitset<LEN_BITS>(bits) << " >>" << endl;    
    bits >>= sizeof(T) * 8 - (end - pos) - 1; 
    cout << " bits3 = " << bitset<LEN_BITS>(bits) << " >>" << endl;
//    bits = invert_bytes(bits);
//    cout << " bits4 = " << bitset<LEN_BITS>(bits) << " <<" << endl;

    return (OUT_T)bits;
}


int main()
{
    uint8_t v[] = { 0x85, 0x80, 0b11001100, 0b11101011 };
    // uint8_t v[] = { 0b01100111, 0b10100110, 0b10101010, 0b11001100 };
    uint16_t n = *((uint16_t*)v);
    uint32_t m = *((uint32_t*)v);
 
    cout << "M = " << bitset<32>(m) << " *********" << endl << endl; 
    cout << "hex: " << hex << m << endl;
    cout << "inv: " << hex << invert_bytes(m) << endl << endl;
    cout << dec; 

    extract_bits_to_le(m, 5, 9);
    extract_bits_to_le(m, 16, 19);
    extract_bits_to_le(m, 14, 28);
}

