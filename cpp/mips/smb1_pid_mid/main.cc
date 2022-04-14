#include <iostream>
#include <iomanip>

using namespace std;

template <class STRUCT_T, typename T>
static STRUCT_T struct_cast(const T n)
{
    static_assert(std::is_integral<T>::value, "Integral type required as T");
    static_assert(std::is_class<STRUCT_T>::value || std::is_union<STRUCT_T>::value, 
                  "class, struct or union type required as STRUCT_T");
    static_assert(sizeof(T) == sizeof(STRUCT_T), "Incompatible types passed");

    return *(reinterpret_cast<const STRUCT_T*>(&n));
}

template <typename T, class STRUCT_T>
static T integral_cast(const STRUCT_T& s)
{
    static_assert(std::is_integral<T>::value, "Integral type required as T");
    static_assert(std::is_class<STRUCT_T>::value || std::is_union<STRUCT_T>::value, 
                  "class, struct or union type type required as STRUCT_T");
    static_assert(sizeof(T) == sizeof(STRUCT_T), "Incompatible types passed");

    return *(reinterpret_cast<const T*>(&s));
}

void print(uint64_t pidmid)
{
    cout << "real bytes: ";
    const uint8_t* p = (uint8_t*)&pidmid;
    for(uint8_t i = 0; i < sizeof(uint64_t); ++i)
    {
        cout << hex << setfill('0') << setw(2) << (uint16_t)(*(p + i)) << ", ";
    }
    cout << dec << endl;
}

uint64_t pid_mid(uint16_t pid_low, uint16_t pid_high, uint16_t mid)
{
    uint64_t pid_mid_pair = (((uint32_t)le16toh(pid_high)) << sizeof(uint16_t) * 8) | le16toh(pid_low);
    pid_mid_pair <<= sizeof(uint32_t) * 8;
    pid_mid_pair |= le16toh(mid);

    return pid_mid_pair;
//    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
//    struct pid_mid_pair_t
//    {
//        uint16_t        pid_low;
//        uint16_t        pid_high;
//        uint32_t        mid;
//    } pid_mid_pair { .pid_low = le16toh(pid_low), .pid_high = le16toh(pid_high), .mid = le16toh(mid) }; 
//    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
//    struct pid_mid_pair_t
//    {
//        uint32_t        mid;
//        uint16_t        pid_high;
//        uint16_t        pid_low; 
//    } pid_mid_pair { .mid = le16toh(mid), .pid_high = le16toh(pid_high), .pid_low = le16toh(pid_low)  }; 
//    #else
//    #error "Unspecified host byte order, please fix 'smb1.h'"
//    #endif
//
//    return integral_cast<uint64_t>(pid_mid_pair);
}

#define PRT(pl, ph, mid) \
cout << hex << "pid_mid(pid_low=0x" << setfill('0') << setw(4) << pl \
     << ", pid_high=0x" << setw(4) << ph  \
     << ", mid=0x" << setw(4) << mid << "): hex: " \
     << setw(16) << pid_mid(pl, ph, mid) << dec << ", dec: " << pid_mid(pl, ph, mid) << endl; \
print(pid_mid(pl, ph, mid)); 

int main()
{
    uint8_t v_ph[] = { 1, 0 }, v_pl[] = { 2, 0 }, v_mid[] = { 4, 0 };
    uint16_t ph = *((uint16_t*)v_ph);
    uint16_t pl = *((uint16_t*)v_pl);
    uint16_t mid = *((uint16_t*)v_mid);
   
    PRT(pl, ph, mid);
    return 0;
}
