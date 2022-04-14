#include <iostream>
#include <iomanip>

using namespace std;

struct handle_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const handle_type_t FILE_ID_HANDLE_TYPE          = 0x0001;
static const handle_t INVALID_FILE_ID_HANDLE            = 0xFFFF;
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

};

void print_handle(uint32_t handle, const std::string& name = "handle")
{
    cout << name << ": " << handle 
         << " ,hex: 0x" << hex << setfill('0') << setw(8) << handle;

    cout << ", bytes = ["
    uint8_t* p = (uint8_t*)&handle;
    for(size_t i = 0; i < 4; ++i)
    {
        cout << setfill('0') << setw(2) << *(p + i);
        if (p != 4)
            cout << ",";
    }

    cout << "]" << dec << endl;

};
