#include <iostream>
#include <iomanip>
#include <endian.h>

using namespace std;

static const uint16_t INVALID_FILE_ID       = 0xFFFF;
static const uint16_t INVALID_SEARCH_ID     = 0;
static const uint16_t INVALID_TR_SUBCOMMAND = 0xFFFF;

typedef uint32_t handle_t;
typedef handle_t handle_type_t;
static const handle_t EMPTY_HANDLE                      = 0x00000000;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const handle_type_t FILE_ID_HANDLE_TYPE          = 0x01000000;
static const handle_t INVALID_FILE_ID_HANDLE            = 0x0100FFFF;
static const handle_type_t SEARCH_ID_HANDLE_TYPE        = 0x02000000;
static const handle_t INVALID_SEARCH_ID_HANDLE          = 0x02000000;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static const handle_type_t FILE_ID_HANDLE_TYPE          = 0x01000000;
static const handle_t INVALID_FILE_ID_HANDLE            = 0xFFFF0001;
static const handle_type_t SEARCH_ID_HANDLE_TYPE        = 0x00000002;
static const handle_t INVALID_SEARCH_ID_HANDLE          = 0x00000002;
#else
#error "Unspecified host byte order, please fix 'smb1.h'"
#endif

handle_t handle(uint32_t id, handle_type_t handle_type = FILE_ID_HANDLE_TYPE)
{ return handle_type | le32toh(id); }

uint16_t id_from_handle(handle_t handle) 
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const handle_t ID_MASK = 0x0000FFFF;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static const handle_t ID_MASK = 0x0000FFFF;
#else
#error "Unspecified host byte order, please fix 'smb1.h'"
#endif
    return handle & ID_MASK; 
}

int main()
{
    uint8_t v[] = { 0x12, 0x00, 0x00, 0x00 };
    uint32_t* p = (uint32_t*)v;
    uint32_t h = handle(*p);

    cout << (*p == 0x12000000) << endl;
    cout << "handle = 0x" << hex << setfill('0') << setw(8) <<  h 
         << ", id = 0x" << setfill('0') << setw(4) << id_from_handle(h) << dec << endl;

    return 0;
}
