#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
    struct tm datetime;
    memset((void*)&datetime, 0, sizeof(struct tm));
    char s[] = "Nov 11 09:41";
    char* p = strptime(s, "%h %d %H:%M:%S", &datetime);
    
    printf("1. Timestamp(ru) = %lu, srptime res = %p\n", mktime(&datetime), p);

    static const size_t BUF_LEN = 512;
    char buf[BUF_LEN];
    strftime(buf, BUF_LEN, "%d.%m.%Y %H:%M:%S", &datetime);
    printf("1. Datetime (ru) = %s\n", buf);

    return 0;
}
