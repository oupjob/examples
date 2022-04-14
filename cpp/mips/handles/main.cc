#include <iostream>
#include <endian.h>
#include <iomanip>

using namespace std;

typedef uint32_t handle_t;
typedef uint32_t handle_type_t;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    static const handle_type_t FILE_ID_HANDLE_TYPE          = 0x01000000;
    static const handle_t INVALID_FILE_ID_HANDLE            = 0x0100FFFF;
    static const handle_type_t SEARCH_ID_HANDLE_TYPE        = 0x02000000;
    static const handle_t INVALID_SEARCH_ID_HANDLE          = 0x02000000;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    static const handle_type_t FILE_ID_HANDLE_TYPE          = 0x00000001;
    static const handle_t INVALID_FILE_ID_HANDLE            = 0xFFFF0001;
    static const handle_type_t SEARCH_ID_HANDLE_TYPE        = 0x00000002;
    static const handle_t INVALID_SEARCH_ID_HANDLE          = 0x00000002;
#else
#error "Unspecified host byte order, please fix 'smb1.h'"
#endif

handle_t handle(uint16_t id, handle_type_t handle_type) 
{
    return le32toh(le16toh(id)) | handle_type;
}

handle_t invalid_handle(handle_t handle)
{
    if (handle & FILE_ID_HANDLE_TYPE)
        return INVALID_FILE_ID_HANDLE;
    else
        return INVALID_SEARCH_ID_HANDLE;
}

void print(handle_t handle)
{
    uint8_t* p = (uint8_t*)&handle;
    cout << "handle = [dec: " << handle << ", hex: ";
    for(size_t i = 0; i < sizeof(handle_t); ++i)
    {
        cout << hex << (uint16_t)(*p) << " ";
        ++p;
    }
    cout << "]" << dec << endl;
}

uint16_t id_from_handle(handle_t h) 
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const handle_t ID_MASK = 0x0000FFFF;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static const handle_t ID_MASK = 0xFFFF0000;
#else
#error "Unspecified host byte order, please fix 'smb1.h'"
#endif
    return le16toh(le32toh(h & ID_MASK)); 
}

//bool is_invalid(handle_t haddle, handle_t h_invalid = invalid_handle(handle))
//{
//    return handle == h_invalid;
//}

int main(void)
{
    uint16_t file_id = le16toh(0xFFFF);
    cout << ((handle(file_id, FILE_ID_HANDLE_TYPE) == INVALID_FILE_ID_HANDLE) ? "Invalid" : "Valid") << " file handle" << endl;
    print(handle(file_id, FILE_ID_HANDLE_TYPE));

    uint16_t search_id = le16toh(0x0000);
    cout << ((handle(search_id, SEARCH_ID_HANDLE_TYPE) == INVALID_SEARCH_ID_HANDLE) ? "Invalid" : "Valid") << " search handle" << endl;
    print(handle(search_id, SEARCH_ID_HANDLE_TYPE));

    cout << "Check invalid_handle():" << endl;
    uint16_t id = le16toh(0x1234);
    handle_t fhandle = handle(id, FILE_ID_HANDLE_TYPE);
    cout << hex << "Invalid file_handle for: " << fhandle << " is: " << invalid_handle(fhandle) << endl;
    
    handle_t shandle = handle(id, SEARCH_ID_HANDLE_TYPE);
    cout << hex << "Invalid search_handle for: " << shandle << " is: " << invalid_handle(shandle) << endl;
  //  cout << "search_handle invalid: " << is_invalid(shandle) << endl;

    cout << "fhandle = 0x" << hex << setfill('0') << setw(8) << fhandle
         << ", fid = 0x" << setfill('0') << setw(4) << id_from_handle(fhandle) 
         << dec << endl;

    cout << "shandle = 0x" << hex << setfill('0') << setw(8) << shandle
         << ", sid = 0x" << setfill('0') << setw(4) << id_from_handle(shandle) 
         << dec << endl;

    return 0;
}
