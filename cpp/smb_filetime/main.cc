#include <iostream>
#include <string>

using namespace std;

struct ntdec_time
{
    uint32_t        sec;
    uint32_t        usec;
};

struct pure_cifs_filetime
{
    uint32_t        low_datetime;
    uint32_t        high_datetime;
} __attribute__((packed));

template <typename T, class STRUCT_T>
T integral_cast(const STRUCT_T& s)
{
    static_assert(std::is_integral<T>::value, "Integral type required as T");
    static_assert(std::is_class<STRUCT_T>::value, "class or struct type required as STRUCT_T");
    static_assert(sizeof(T) == sizeof(STRUCT_T), "Incompatible types passed");

    return *(reinterpret_cast<const T*>(&s));
}

ntdec_time smb_filetime_to_ntdec_time(const pure_cifs_filetime& filetime)
{
    static const uint64_t TICKS_PER_SECOND = 10000000;
    static const uint64_t EPOCH_DIFFERENCE = 11644473600LL; // 1601 г. - 1970 г. в секундах
    uint64_t ull_filetime = integral_cast<uint64_t>(filetime);
    uint64_t sec, usec;

    sec = ull_filetime / TICKS_PER_SECOND;
    usec = ull_filetime - sec * TICKS_PER_SECOND;
    sec = sec - EPOCH_DIFFERENCE;
    
    return ntdec_time {(uint32_t)sec, (uint32_t)usec};
}

int main()
{
    uint8_t v[] = { 0x15, 0xab, 0x3a, 0x37, 0x38, 0x3c, 0xd7, 0x01 };
    pure_cifs_filetime* p = (pure_cifs_filetime*)v;
    
    ntdec_time ntime = smb_filetime_to_ntdec_time(*p);
    char buf[256];
    size_t n = strftime(buf, 256, "%d/%m/%Y %T", localtime((time_t*)(&(ntime.sec))) );

    cout << ntime.sec << ", " << buf << endl;
}

