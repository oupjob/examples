#include <iostream>
#include <iomanip>

using namespace std;

enum class ACCESS_MODE : uint16_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    OPEN_READ           = 0x0000,
    OPEN_WRITE          = 0x0001,
    OPEN_READ_WRITE     = 0x0002,
    OPEN_EXECUTE        = 0x0003,

    SHARE_COMPATIBILITY_MODE        = 0x0000,
    SHARE_DENY_READ_WRITE_EXECUTE   = 0x0010,
    SHARE_DENY_WRITE                = 0x0020,
    SHARE_DENY_READ_EXECUTE         = 0x0030,
    SHARE_DENY_NOTHING              = 0x0040,

    REF_LOCALITY_UNKNOWN                    = 0x0000,
    REF_LOCALITY_MAINLY_SEQUENTIAL_ACCESS   = 0x0100,
    REF_LOCALITY_MAINLY_RANDOM_ACCESS       = 0x0200,
    REF_LOCALITY_MAINLY_RANDOM_ACCESS_SOME_LOCALITY = 0x0200,

    CACHE_FILE          = 0x1000,

    WRITETHROUGH        = 0x4000
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    OPEN_READ           = 0x0000,
    OPEN_WRITE          = 0x0100,
    OPEN_READ_WRITE     = 0x0200,
    OPEN_EXECUTE        = 0x0300,

    SHARE_COMPATIBILITY_MODE        = 0x0000,
    SHARE_DENY_READ_WRITE_EXECUTE   = 0x1000,
    SHARE_DENY_WRITE                = 0x2000,
    SHARE_DENY_READ_EXECUTE         = 0x3000,
    SHARE_DENY_NOTHING              = 0x4000,

    REF_LOCALITY_UNKNOWN                    = 0x0000,
    REF_LOCALITY_MAINLY_SEQUENTIAL_ACCESS   = 0x0001,
    REF_LOCALITY_MAINLY_RANDOM_ACCESS       = 0x0002,
    REF_LOCALITY_MAINLY_RANDOM_ACCESS_SOME_LOCALITY = 0x0002,

    CACHE_FILE          = 0x0010,

    WRITETHROUGH        = 0x0040
#else 
#error "Unspecified host byte order, please fix 'smb1_defs.h'"
#endif
};

#define prt(val, expected) \
cout << "value = " << hex <<  val << ((val == static_cast<uint16_t>(ACCESS_MODE::expected)) ? " == " : " != ") \
     << #expected << "(" << static_cast<uint16_t>(ACCESS_MODE::expected) << ")" << dec << endl;

int main()
{
    uint8_t v[] = { 0x03, 0x00 };
    uint16_t* p = (uint16_t*)v;
    prt((*p), OPEN_EXECUTE); 

    return 0;
}
