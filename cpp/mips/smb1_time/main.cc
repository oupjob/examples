#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef uint16_t pure_smb1_time;

uint32_t smb_time_to_utime(uint16_t smb_date, uint16_t smb_time)
{
    static const uint16_t SMB_TIME_BEGIN_YEAR = 1980;
    static const uint16_t STRUCT_TM_BEGIN_YEAR = 1900;
    static const uint16_t YEAR_DIFF = SMB_TIME_BEGIN_YEAR - STRUCT_TM_BEGIN_YEAR;
    static const uint16_t JANUARY = 1;
    static const uint8_t YEAR_BIT_SHIFT = 9;
    static const uint8_t MON_BIT_SHIFT = 5;
    static const uint8_t HOUR_BIT_SHIFT = 11;
    static const uint8_t MIN_BIT_SHIFT = 5;

    enum class SMB_DATE_MASK : uint16_t
    {
//  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        YEAR        = 0xFE00,   // 7 bits first
        MONTH       = 0x01E0,   // 4 bits middle
        DAY         = 0x001F    // 5 bits end
//  #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
//      YEAR        = 0x00FE,   // 7 bits first
//      MONTH       = 0x01E0,   // 4 bits middle
//      DAY         = 0x1F00    // 5 bits end 
//  #endif
    };

    enum class SMB_TIME_MASK : uint16_t
    {
//    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        HOUR        = 0xF800,   // 5 bits first
        MINUTES     = 0x07E0,   // 6 bits middle
        SECONDS     = 0x001F    // 5 bits end
//    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
//        HOUR        = 0x00F8,   // 5 bits first
//        MINUTES     = 0x07E0,   // 6 bits middle
//        SECONDS     = 0x1F00    // 5 bits end
//    #endif
    };

    tm time;

    smb_date = le16toh(smb_date);
    smb_time = le16toh(smb_time);

    time.tm_year = ((smb_date & static_cast<uint16_t>(SMB_DATE_MASK::YEAR)) >> YEAR_BIT_SHIFT) + YEAR_DIFF;
    time.tm_mon = ((smb_date & static_cast<uint16_t>(SMB_DATE_MASK::MONTH)) >> MON_BIT_SHIFT) - JANUARY;
    time.tm_mday = (smb_date & static_cast<uint16_t>(SMB_DATE_MASK::DAY));

    time.tm_hour = (smb_time & static_cast<uint16_t>(SMB_TIME_MASK::HOUR)) >> HOUR_BIT_SHIFT;
    time.tm_min = (smb_time & static_cast<uint16_t>(SMB_TIME_MASK::MINUTES)) >> MIN_BIT_SHIFT;
    time.tm_sec = smb_time & static_cast<uint16_t>(SMB_TIME_MASK::SECONDS);

    cout << time.tm_year << "." << time.tm_mon << "." << time.tm_mday << " -- "
         << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << endl; 

    return mktime(&time);      
}

int main()
{
    uint8_t v_date[] = { 0b01100011, 0b01010010 }; // (LE: 0bMMMDDDDD 0bYYYYYYYM) (BE: )
    uint8_t v_time[] = { 0b11100101, 0b10011011 }; // (LE: 0bMMMSSSSS 0bHHHHHMMM) (BE: )

    uint16_t* p_date = (uint16_t*)v_date;
    uint16_t* p_time = (uint16_t*)v_time; 

    uint32_t utime = smb_time_to_utime(*p_date, *p_time);
    time_t time_ = utime;

    tm* time = localtime(&time_);

    char buf[128];
    strftime(buf, sizeof(buf), "%Y.%m.%d // %k:%M:%S", time);

    cout << buf << endl;

//    free(time);
    return 0;
}
