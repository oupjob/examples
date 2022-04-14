#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string.h>
#include <iomanip>
#include <endian.h>

    
struct dw_version_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    enum class VERSION : uint32_t
    {
        CERT_CHAIN_VERSION_1        = 0x00000001,
        CERT_CHAIN_VERSION_2        = 0x00000002
    };

    uint32_t        version1:8;
    uint32_t        version2:8;
    uint32_t        version3:8;

    uint32_t        t_bit:1;
    uint32_t        version4:7;      // VERSION
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    enum class VERSION : uint32_t
    {
        CERT_CHAIN_VERSION_1        = 0x01000000,
        CERT_CHAIN_VERSION_2        = 0x02000000
    };

    uint32_t        version1:8;
    uint32_t        version2:8;
    uint32_t        version3:8;

    uint32_t        version4:7;      // VERSION
    uint32_t        t_bit:1;
#else
#error "Unspecified host byte order, please fix 'rdp_mcs_connection_rq_rsp_defs.h'"
#endif

    uint32_t version() 
    {
        bool tmp_t_bit = t_bit;
        t_bit = 0;
        uint32_t vers;
        memcpy(reinterpret_cast<void*>(&vers), reinterpret_cast<const void*>(this), sizeof(vers));
        t_bit = tmp_t_bit;
        return le32toh(vers);
    }
};

using namespace std;

#define PRT(p, field, letoh) cout << hex << "dw_version->" #field ": " << "0x" << letoh(p->field) << dec << endl; 

void print_v(const uint8_t* v)
{
    cout << "v: ";
    for(size_t i = 0; i < 4; ++i)
    {
        cout << hex << "0x" << (uint16_t)v[i] << " ";
    }
    cout << endl;
}

int main()
{
    uint8_t v[] = { 0x02, 0x00, 0x00, 0x01 };
    dw_version_t* p = (dw_version_t*)v;
    
    // p->t_bit = 1;
    // p->version = 2;
    
    print_v(v);
    
    PRT(p, version(), );
    PRT(p, t_bit, );

    cout << "version == 2: " << (p->version() == 2) << endl;
}


