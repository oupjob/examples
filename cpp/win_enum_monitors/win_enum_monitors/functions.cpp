#include "functions.h"
#include <PhysicalMonitorEnumerationAPI.h>
#include <DXGI.h>
#include <WinIoCtl.h>

void enumDumpDisplayDevices() {
    DWORD               iDevNum = 0;
    DISPLAY_DEVICE      DisplayDevice;
    DisplayDevice.cb = sizeof( DISPLAY_DEVICE );
//    DEVMODE             DeviceMode;
    HDC                 hDcDevice;

    while( EnumDisplayDevices( NULL, iDevNum, &DisplayDevice, DISPLAY_DEVICE_ACTIVE ) ) {
        _tprintf(
            TEXT( "\nDeviceID: '%s' | DeviceKey: '%s' | DeviceName: '%s' | DeviceString: '%s' | StateFlags: '0x%x' \n" ),
            DisplayDevice.DeviceID,
            DisplayDevice.DeviceKey,
            DisplayDevice.DeviceName,
            DisplayDevice.DeviceString,
            DisplayDevice.StateFlags
        );

        hDcDevice = CreateDC( NULL, DisplayDevice.DeviceID, NULL, NULL );

//        memset( &DeviceMode, 0, sizeof(DEVMODE) );
//        DeviceMode.dmSize = sizeof( DEVMODE );
//        if( EnumDisplaySettings( DisplayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &DeviceMode ) ) {
//            _tprintf( TEXT( "\tDevice Mode Settings:\n") );
//            _tprintf( TEXT("\tdmPosition: %d , %d\n"), DeviceMode.dmPosition.x, DeviceMode.dmPosition.y );
//            _tprintf( TEXT("\tdmSize: %d\n"), DeviceMode.dmSize );
//            _tprintf( TEXT("\tdmDisplayOrientation: %d\n"), DeviceMode.dmDisplayOrientation );
//            _tprintf( TEXT("\tdmPanningWidth: %d\n"), DeviceMode.dmPanningWidth );
//            _tprintf( TEXT("\tdmPanningHeigth: %d\n"), DeviceMode.dmPanningHeight );
//            _tprintf( TEXT("\tdmMediaType: %d\n"), DeviceMode.dmMediaType );
//        }
        ++iDevNum;
    }
}

void enumDumpDisplayMonitors() {
//  HDC hdc = GetDC( NULL );
    while( EnumDisplayMonitors( NULL, NULL, DumpMonitorEnumProc, NULL ) ) {}
}

BOOL CALLBACK DumpMonitorEnumProc(
    _In_ HMONITOR hMonitor,
    _In_ HDC      hdcMonitor,
    _In_ LPRECT   lprcMonitor,
    _In_ LPARAM   dwData
) {
    static DWORD MonitorIndex = 0;
    DWORD NumOfMonitors = 0;
    if ( !GetNumberOfPhysicalMonitorsFromHMONITOR( hMonitor, &NumOfMonitors ) || MonitorIndex >= NumOfMonitors )
        return false;

    HDC hDcMonitor;
    MONITORINFOEX MonInfo;
    MonInfo.cbSize = sizeof( MONITORINFOEX );
    if( GetMonitorInfo( hMonitor, &MonInfo ) ) {
        hDcMonitor = CreateDC( NULL, MonInfo.szDevice, NULL, NULL );
        int color_depth = GetDeviceCaps( hDcMonitor, BITSPIXEL );
        int vrefresh = GetDeviceCaps( hDcMonitor, VREFRESH );
        DeleteDC( hDcMonitor );

        _tprintf(
//            TEXT("Monitor: rcMonitor( top=%d, left=%d, bottom=%d, right=%d ) | rcWork( top=%d, left=%d, bottom=%d, right=%d ) | szDevice: %s\n"),
            TEXT("\nMonitor: szDevice: %s | rcMonitor[top,left,bottom,right](%ld,%ld,%ld,%ld) | rcWork[top,left,bottom,right](%ld,%ld,%ld,%ld) | ColorDepth: %d | VRefresh: %d\n"),
            MonInfo.szDevice,
            MonInfo.rcMonitor.top, MonInfo.rcMonitor.left, MonInfo.rcMonitor.bottom, MonInfo.rcMonitor.right,
            MonInfo.rcWork.top, MonInfo.rcWork.left, MonInfo.rcWork.bottom, MonInfo.rcWork.right,
            color_depth,
            vrefresh
        );
    }

    MonitorIndex++;
    return true;
}

void enumDumpGraphicAdaptersUsingDXGI() {
    IDXGIFactory * pFactory = NULL;
    IDXGIAdapter * pAdapter;

    if ( FAILED( CreateDXGIFactory(__uuidof(IDXGIFactory) ,(void**)&pFactory) ) ) {
        _tprintf( TEXT( "Failed action: CreateDXGIFactory" ) );
        exit( 1 );
    }

    DXGI_ADAPTER_DESC sAdapterDesc;
    memset( &sAdapterDesc, 0, sizeof( DXGI_ADAPTER_DESC ) );
    for ( UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i ) {
        if ( pAdapter->GetDesc( &sAdapterDesc ) == S_OK ) {
            _tprintf(
                TEXT( "\nDXGI_ADAPTER_DESC: Descripton: %s | VendorId: 0x%x | DeviceId: 0x%x | SubSysId: 0x%x | SharedSystemMemory: %d | DedicatedVideoMemory: %d | DedicatedSystemMemory %d" ),
                sAdapterDesc.Description,
                sAdapterDesc.VendorId,
                sAdapterDesc.DeviceId,
                sAdapterDesc.SubSysId,
                sAdapterDesc.SharedSystemMemory,
                sAdapterDesc.DedicatedVideoMemory,
                sAdapterDesc.DedicatedSystemMemory
            );
        }
    }
}