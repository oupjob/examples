#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _UNICODE
#include <Windows.h>
#include <tchar.h>

BOOL CALLBACK DumpMonitorEnumProc(
    _In_ HMONITOR hMonitor,
    _In_ HDC      hdcMonitor,
    _In_ LPRECT   lprcMonitor,
    _In_ LPARAM   dwData
);

void enumDumpDisplayDevices();
void enumDumpDisplayMonitors();
void enumDumpGraphicAdaptersUsingDXGI();
void enumDumpGraphicAdaptersUsingDxDiag();

#endif // FUNCTIONS_H
