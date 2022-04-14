#include <arpa/inet.h>
#include <iostream>
#include <iomanip>

using namespace std;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
enum class UINT32_STATUS : uint32_t
{
    STATUS_LOGON_TYPE_NOT_GRANTED     = 0xC000015B
};

enum class CODE : uint16_t
{
    STATUS_LOGON_TYPE_NOT_GRANTED     = 0x015B
};

struct nt_status_t
{
    uint32_t        code_pt2:8;
    uint32_t        code_pt1:8;

    uint32_t        facilty_pt2:8;
    uint32_t        facilty_pt1:4;

    uint32_t        n_bit:1;
    uint32_t        c_bit:1;
    uint32_t        sev:2;  // SEVERITY

    uint16_t facilty() const { return htons((facilty_pt2 << 8) + facilty_pt1); }
    uint16_t code() const { return htons((code_pt2 << 8) + code_pt1); }
};

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
enum class UINT32_STATUS : uint32_t
{
    STATUS_LOGON_TYPE_NOT_GRANTED     = 0x5B0100C0
};

enum class CODE : uint16_t
{
    STATUS_LOGON_TYPE_NOT_GRANTED     = 0x5B01
};

struct nt_status_t
{
    uint32_t        code_pt2:8;
    uint32_t        code_pt1:8;

    uint32_t        facilty_pt2:8;

    uint32_t        sev:2;  // SEVERITY
    uint32_t        c_bit:1;
    uint32_t        n_bit:1;
    uint32_t        facilty_pt1:4;

    uint16_t facilty() const { return htons((facilty_pt2 << 8) + facilty_pt1); }
    uint16_t code() const { return htons((code_pt2 << 8) + code_pt1); }
    
    // uint16_t facilty() const { return (facilty_pt2 << 4) + facilty_pt1; }
    // uint16_t code() const { return (code_pt2 << 8) + code_pt1; }
};

#endif

template <class STRUCT_T, typename T>
STRUCT_T struct_cast(const T n)
{
    return *(reinterpret_cast<const STRUCT_T*>(&n));
}

template <typename T, class STRUCT_T>
T integral_cast(const STRUCT_T& s)
{
    return *(reinterpret_cast<const T*>(&s));
}

#define prtf(f) cout << #f " = " << hex << f << dec << endl;

template <typename T>
void prt(const char* prefix, T status)
{
    uint8_t *p = (uint8_t*)&status, *p_end = p + sizeof(T);
    
    cout << prefix;
    for(; p != p_end; ++p)
        cout << hex << ((uint16_t)*p) << " ";
    cout << dec << endl;
}

int main()
{
    uint8_t v[] = { 0x5B, 0x01, 0, 0xC0 };
    uint32_t status = *((uint32_t*)v);

    prt("Status: ", status);
    cout << "Status: " << hex << status << dec << endl;
    if (status == static_cast<uint32_t>(UINT32_STATUS::STATUS_LOGON_TYPE_NOT_GRANTED))
        cout << "status == STATUS_LOGON_TYPE_NOT_GRANTED" << endl;
    else
        cout << "status != STATUS_LOGON_TYPE_NOT_GRANTED" << endl;

    nt_status_t ntstat = struct_cast<nt_status_t>(status);
    prt("Code: ", ntstat.code());
    cout << "Code: " << hex << ntstat.code() << dec << endl;
    if (ntstat.code() == static_cast<uint16_t>(CODE::STATUS_LOGON_TYPE_NOT_GRANTED))
        cout << "code == STATUS_LOGON_TYPE_NOT_GRANTED" << endl;
    else
        cout << "code != STATUS_LOGON_TYPE_NOT_GRANTED" << endl;

    prtf(ntstat.code_pt1);
    prtf(ntstat.code_pt2);

    return 0;
}
