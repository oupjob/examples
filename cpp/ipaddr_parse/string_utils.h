#ifndef STRING_UTILS_H
#define STRING_UTILS_H
//------------------------------------------------------------------------------
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cstdarg>
#include <stdint.h>
#include <algorithm>
#include <iconv.h>
#include <errno.h>
#include <vector>
//------------------------------------------------------------------------------
namespace string_utils
{
//------------------------------------------------------------------------------
inline bool charcmp(uint8_t a, uint8_t b, bool match_case = false)
{
    if (a == b)
        return true;
    if (!match_case && a >= 'A' && a <= 'Z')
        return (a | 0x20) == (b | 0x20);
    return false;
}
//------------------------------------------------------------------------------
inline bool charcmp(char a, char b, bool match_case = false)
{
    return charcmp((uint8_t) a, (uint8_t) b, match_case);
}
//------------------------------------------------------------------------------
inline bool wildcmp(const uint8_t* wild, size_t wildlen, const uint8_t* mem, size_t memlen, bool match_case = false, uint8_t any = '*', uint8_t one = '?')
{
#define NEOS(s, f) (f != 0 ? s < f : *s != 0)

    const uint8_t* cp = 0;
    const uint8_t* mp = 0;

    const uint8_t* wildend = wildlen > 0 ? wild + wildlen : 0;
    const uint8_t* memend = memlen > 0 ? mem + memlen : 0;

    while ((NEOS(mem, memend)) && (*wild != any))
    {
        if ((!charcmp(*wild, *mem, match_case)) && (*wild != one))
            return false;
        ++wild;
        ++mem;
    }

    while (NEOS(mem, memend))
    {
        if (*wild == any)
        {
            if (!NEOS(++wild, wildend))
                return true;
            mp = wild;
            cp = mem + 1;
        }
        else if ((charcmp(*wild, *mem, match_case)) || (*wild == one))
        {
            ++wild;
            ++mem;
        }
        else
        {
            wild = mp;
            mem = cp++;
        }
    }

    while (*wild == any && NEOS(++wild, wildend)){};
    return wildend ? wild == wildend : *wild == 0;
}
//------------------------------------------------------------------------------
inline bool wildcmp(const char* wild, size_t wildlen, const char* mem, size_t memlen, bool match_case = false, char any = '*', char one = '?')
{
    return wildcmp((const uint8_t*)wild, wildlen, (const uint8_t*)mem, memlen, match_case, (uint8_t)any, (uint8_t)one);
}
//------------------------------------------------------------------------------
inline int wildcmp(const char* wild, const char* str, size_t str_len = 0, bool match_case = false)
{
    return wildcmp(wild, 0, str, str_len, match_case);
}
//------------------------------------------------------------------------------
inline bool match(const std::string& checked, const std::string& mask, bool match_case)
{
    return wildcmp((const uint8_t*)mask.data(), mask.length(), (const uint8_t*) checked.data(), checked.length(), match_case);
}
//------------------------------------------------------------------------------
inline std::string trim_left(const std::string& value, const char* chars2remove)
{
    if (!value.empty())
    {
        std::string::size_type pos = value.find_first_not_of(chars2remove);
        if (pos == std::string::npos)
            return std::string();
        if (pos > 0)
            return value.substr(pos);
    }
    return value;
}
//------------------------------------------------------------------------------
inline std::string trim_right(const std::string& value, const char chars2remove = ' ')
{
    if (!value.empty())
    {
        std::string::size_type pos = value.find_last_not_of(chars2remove);
        if (pos == std::string::npos)
            return std::string();
        if (pos < value.size() - 1)
            return value.substr(0, pos + 1);
    }
    return value;
}
//------------------------------------------------------------------------------
inline std::string trim(const std::string& value, const char chars2remove = ' ')
{
    if (!value.empty())
    {
        std::string::size_type pos_start = value.find_first_not_of(chars2remove);
        std::string::size_type pos_end   = value.find_last_not_of (chars2remove);
        if (pos_start == std::string::npos)
            return std::string();
        if (pos_start > 0)
        {
            if (pos_end < value.size() - 1)
                return value.substr(pos_start, pos_end - pos_start);
            else
                return value.substr(pos_start);
        }
        else if (pos_end < value.size() - 1)
            return value.substr(0, pos_end + 1);
    }
    return value;
}
//------------------------------------------------------------------------------
inline std::vector<std::string> split(const char* str, size_t length, const char* splitter = " ")
{
    std::vector<std::string> elems;
    const char* p = str;
    const char* b = str;
    const char* e = str + length;
    while (p < e)
    {
        if (strchr(splitter, *p) != 0)
        {
            if (p - b > 0)
                elems.push_back(std::string(b, p - b));
            b = p + 1;
        }
        ++p;
    }
    if (e - b > 0)
        elems.push_back(std::string(b, e - b));
    return elems;
}
//------------------------------------------------------------------------------
inline std::vector<std::string> split(const std::string& str, const char* splitter = " ")
{
    return split(str.c_str(), str.length(), splitter);
}
//------------------------------------------------------------------------------
inline std::string join(const std::vector<std::string>& strs, const char* splitter = 0)
{
    std::string res;
    res.reserve(strs.size() * strs[0].length() * 3 / 2);
    for (std::vector<std::string>::const_iterator it = strs.begin(); it != strs.end(); ++it)
    {
        if (splitter != 0 && res.length() > 0)
            res.append(splitter);
        res.append(*it);
    }
    return res;
}
//------------------------------------------------------------------------------
inline bool is_digit(const std::string& value)
{
    bool is_hex = value.find("0x") == 0;
    for (std::string::const_iterator it = value.begin() + (is_hex ? 2 : 0);
         it < value.end(); ++it)
    {
        char ch = *it;
        bool is_digit = (('0' <= ch && ch <= '9') ||
                         (is_hex && (('a' <= ch && ch <= 'd') ||
                                     ('A' <= ch && ch <= 'D'))));
        if (!is_digit)
            return false;
    }
    return true;
}
//------------------------------------------------------------------------------
inline int to_int(const std::string& value)
{
    if (value.find("0x") == 0)
    {
        int integer = 0;
        sscanf(value.c_str(), "0x%x", &integer);
        return integer;
    }
    else
        return atoi(value.c_str());
}
//------------------------------------------------------------------------------
/*inline std::string to_lower(const char* str, size_t length)
{
    std::string result;
    result.resize(length);
    std::transform(str, str + length, result.begin(), tolower);
    return result;
}*/
//------------------------------------------------------------------------------
inline std::string convert(const char* from, const char* to, const char* what, size_t length = 0)
{
    std::string converted;

    if (!(from && to && what))
        return std::string();

    iconv_t icd = iconv_open(to, from);
    if (icd == (iconv_t) -1)
        return std::string();

    if (length == 0)
        length = strlen(what);

    converted.resize(length * 4);

    char* inbuf __attribute__((unused))  = const_cast<char*> (what);
    char* outbuf = const_cast<char*> (converted.data());
    size_t inbytesleft   = length;
    size_t outbytesleft  = converted.length();
#if defined (OCTEON_BUILD) && (OCTEON_SDK_VERSION_NUM < 301000555ull)
    if (iconv(icd, &what, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1)
#else
    if (iconv(icd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1)
#endif
    {
        printf("iconv: convert failed: %s\n", strerror(errno));
        fflush(stdout);
    }
    iconv_close(icd);

    if (inbytesleft != 0)
        return std::string();

    converted.resize(converted.length() - outbytesleft);
    return converted;
}
//------------------------------------------------------------------------------
inline std::string url_decode(const char* src, size_t length)
{
    static const unsigned char UM = (unsigned char)(-1);
    const static unsigned char HEX2DEC[256] =
    {
        /*       0   1   2   3    4   5   6   7    8   9   A   B    C   D   E   F */
        /* 0 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 1 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 2 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 3 */  0,  1,  2,  3,   4,  5,  6,  7,   8,  9, UM, UM,  UM, UM, UM, UM,

        /* 4 */ UM, 10, 11, 12,  13, 14, 15, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 5 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 6 */ UM, 10, 11, 12,  13, 14, 15, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 7 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,

        /* 8 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* 9 */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* A */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* B */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,

        /* C */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* D */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* E */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,
        /* F */ UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM,  UM, UM, UM, UM
    };

    std::string converted;
    converted.resize(length);
    char* dst = const_cast<char*>(converted.data());
    const char* src_end = src + length;
    const char* src_last = src_end - 2;
    size_t dst_length = 0;
    while (src < src_last)
    {
        if (*src == '%')
        {
            unsigned char dec1, dec2;
            if ((dec1 = HEX2DEC[(uint8_t)*(src + 1)]) != UM &&
                (dec2 = HEX2DEC[(uint8_t)*(src + 2)]) != UM)
            {
                *dst = (dec1 << 4) + dec2;
                ++dst;
                ++dst_length;
                src += 3;
                continue;
            }
        }
        *dst++ = *src++;
        ++dst_length;
    }
    while (src < src_end)
    {
        *dst++ = *src++;
        ++dst_length;
    }

   converted.resize(dst_length);
   return converted;
}
//------------------------------------------------------------------------------
inline std::string url_decode(const std::string& url)
{
    return url_decode(url.c_str(), url.length());
}
//------------------------------------------------------------------------------
inline std::string to_str(const char* fmt, ...)
{
    std::string res;

    va_list args;
    va_start(args, fmt);

    size_t size = 64;
    for (int i = 0; i < 4; ++i)
    {
        res.resize(size);
        char* buf = const_cast<char*> (res.data());
        int result = vsnprintf(buf, size, fmt, args);
        if (result != -1)
        {
            res.resize(result);
            break;
        }
        buf[size - 1] = 0;
        size *= 2;
    }
    va_end(args);
    return res;
}
//------------------------------------------------------------------------------
inline std::string format(const char* fmt, ...)
{
    std::string res;

    va_list args;
    va_start(args, fmt);

    char b;
    int length = vsnprintf(&b, 1, fmt, args);
    if (length > 0)
    {
        va_start(args, fmt); // vsnpritnf меняет внутренность args
        res.resize(length + 1); // да, на конце строики всегда будет болтаться лишний байт
        char* buf = const_cast<char*> (res.data());
        vsnprintf(buf, length + 1, fmt, args);
        res.resize(length);
    }
    va_end(args);
    return res;
}
//------------------------------------------------------------------------------
// вернёт 0, если неправильные данные
inline int str_2_hex(const char* in, int in_len, uint8_t* out, int out_len)
{
    if(in_len % 2 != 0)
        return 0;

    if(in_len > 2 * out_len)
        return 0;

    const char* curr_in = in;
    uint8_t* curr_out = out;

    char tmp[4];
    tmp[2] = 0;
    char* eptr = NULL;

    while(curr_in != in + in_len)
    {
        tmp[0] = *(curr_in++);
        tmp[1] = *(curr_in++);
        *(curr_out++) = strtoul(tmp, &eptr, 16);
        if(eptr != tmp + 2)
            return 0;
    }

    return (curr_out - out);
}
//-----------------------------------------------------------------------------
// вернёт 0, если неправильные данные
// не ставит завершающий '\0'
inline int hex_2_str(const void* in, int in_len, char* out, int out_len)
{
    if(out_len < 2 * in_len)
        return 0;

    static const char* prnt_byte[256] = {
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
        "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
        "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
        "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
        "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
        "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
        "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
        "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
        "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
        "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
        "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
        "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
        "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
    };

    const uint8_t* curr_in = (const uint8_t*)in;
    char* curr_out = out;

    while(curr_in != (const uint8_t*)in + in_len)
    {
        *(uint16_t*)curr_out = *(uint16_t*)prnt_byte[*curr_in];
        curr_out += 2;
        ++curr_in;
    }

    return (curr_out - out);
}
//-----------------------------------------------------------------------------

inline std::string first8_hex_2_str1(const void* in, int in_len)
{
    char buff[32];
    if(in_len > 8) in_len = 8;
    *(buff + hex_2_str(in, in_len, buff, 2 * in_len)) = 0;
    return buff;
}

inline std::string first8_hex_2_str2(const void* in, int in_len)
{
    char buff[32];
    if(in_len > 8) in_len = 8;
    *(buff + hex_2_str(in, in_len, buff, 2 * in_len)) = 0;
    return buff;
}

inline std::string first8_hex_2_str3(const void* in, int in_len)
{
    char buff[32];
    if(in_len > 8) in_len = 8;
    *(buff + hex_2_str(in, in_len, buff, 2 * in_len)) = 0;
    return buff;
}

inline std::string first8_hex_2_str4(const void* in, int in_len)
{
    char buff[32];
    if(in_len > 8) in_len = 8;
    *(buff + hex_2_str(in, in_len, buff, 2 * in_len)) = 0;
    return buff;
}
//-----------------------------------------------------------------------------

template <template<class, class...> class C, class T, class... R>
std::string to_string (const C<T, R...>& c)
{
    if (c.empty())
        return "";

    std::ostringstream os;
    auto x = c.begin();
    os << *x;
    while (++x != c.end())
        os << ", " << *x;

    return os.str();

}

} // end of namespace string_utils
#endif // STRING_UTILS_H
