#include <stdio.h>
#include <Windows.h>
#include "functions.h"

// To continue the enumeration, return TRUE.
// To stop the enumeration, return FALSE.

//BOOL CALLBACK MonitorEnumProc(
//    _In_ HMONITOR hMonitor,
//    _In_ HDC      hdcMonitor,
//    _In_ LPRECT   lprcMonitor,
//    _In_ LPARAM   dwData
//) {

//}

void usage() {
_tprintf(
TEXT(
"Usage: win_enum_monitors [options]\n\
    -d -- enumerate display device\n\
    -m -- enumerate display monitors\n\
    -h -- get this help\n\
Also, call without options for get this help\n"
)
);
}

int main( int argc, char** argv )
{
    if ( argc > 1 ) {
        for( int i = 1; i < argc; ++i ) {
            if ( !strncmp( "-m", argv[ i ], 2 ) ) {
                enumDumpDisplayMonitors();
            } else if ( !strncmp( "-d", argv[ i ], 2 )  ) {
                enumDumpDisplayDevices();
            } else if ( !strncmp( "-a", argv[ i ], 2 ) ) {
                enumDumpGraphicAdaptersUsingDXGI();
            } else if ( !strncmp( "-h", argv[ i ], 2 )  ) {
                usage();
                return 0;
            }
        }
    } else {
        usage();
    }
    return 0;
}

