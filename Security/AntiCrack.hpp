#pragma once
#include <Includes/Includes.hpp>
#include <Security/Api/structs/structs.hpp>
#include <Core/SDK/Structs/Structs.hpp>
#include <Auth/lazyimporter.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <Psapi.h>
#include <thread>
#include <chrono>

#pragma comment(lib, "Psapi.lib")

#define close_app SafeCall(ExitProcess)( 0 );
#define force_crash abort( );

namespace AntiCrack {
BOOL CALLBACK enum_windows_callback( HWND hWnd, LPARAM lparam ) {
const std::vector<std::string> bad_titles =
{
xorstr("httpdebugger"),
xorstr("http debugger"),
xorstr("x64dbg"),
xorstr("debugger"),
xorstr("disassembler"),
xorstr("decompiler"),
xorstr("fiddler"),
xorstr("wireshark"),
xorstr("string search"),
xorstr("process list"),
xorstr("memory viewer"),
xorstr("system informer"),
xorstr("process hacker"),
xorstr("ghidra"),
xorstr("binary ninja"),
xorstr("hyperdbg"),
xorstr("process explorer - sysinternals"),
xorstr("extreme dumper"),
xorstr("add address"),
xorstr("process telerik"),
xorstr("scylla"),
xorstr("referenced strings"),
xorstr("dissect code"),
xorstr("beamer"),
xorstr("windbg"),
xorstr("ksdumper"),
xorstr("import reconstructor"),
xorstr("httpdebuggerui"),
xorstr("analysis tool"),
xorstr("ollydbg"),
xorstr("network traffic dump tool"),
xorstr("petool"),
xorstr("wireshark packet sniffer"),
xorstr("part of sysinternals suite"),
xorstr("network analyzer"),
xorstr("[elevated]"),
xorstr("[codecave hook]"),
xorstr("codecave hook"),
};
int length = SafeCall(GetWindowTextLengthA)( hWnd );
char * buffer = new char[ length + 1 ];
SafeCall(GetWindowTextA)( hWnd, buffer, length + 1 );
std::string title( buffer );
std::transform( title.begin( ), title.end( ), title.begin( ), ::tolower );
if ( SafeCall(IsWindowVisible)( hWnd ) && length != 0 ) {
for ( std::string s : bad_titles ) {
if ( title.find( s ) != std::string::npos ) {
close_app;
return TRUE;
}
}
}
return TRUE;
}
bool FindHookInAddr( BYTE * func ) {
if ( func[ 0 ] == 0xE9 ) {
return true;
}
if ( func[ 0 ] == 0xFF && func[ 1 ] == 0x25 ) {
return true;
}
if ( func[ 0 ] == 0x90 && func[ 1 ] == 0x90 && func[ 2 ] == 0xE9 ) {
return true;
}
return false;
}
void StopService( const char * service_name ) {
        SC_HANDLE service_manager = SafeCall(OpenSCManagerA)( nullptr, nullptr, SC_MANAGER_ALL_ACCESS );
        if ( !service_manager ) { return; }
        SC_HANDLE service_handle = SafeCall(OpenServiceA)( service_manager, service_name, SERVICE_QUERY_STATUS );
        if ( service_handle ) {
            SERVICE_STATUS serviceStatus;
            if ( SafeCall(QueryServiceStatus)( service_handle, &serviceStatus ) && serviceStatus.dwCurrentState == SERVICE_STOPPED ) {
                SafeCall(CloseServiceHandle)( service_handle );
            }
            SafeCall(CloseServiceHandle)( service_handle );
            SC_HANDLE stopServiceHandle = SafeCall(OpenServiceA)( service_manager, service_name, SERVICE_STOP );
            SERVICE_STATUS stopServiceStatus;
            SafeCall(ControlService)( stopServiceHandle, SERVICE_CONTROL_STOP, &stopServiceStatus );
            SafeCall(CloseServiceHandle)( stopServiceHandle );
            std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );
            SC_HANDLE queryServiceHandle = SafeCall(OpenServiceA)( service_manager, service_name, SERVICE_QUERY_STATUS );
            SafeCall(CloseServiceHandle)( queryServiceHandle );
        }
        SafeCall(CloseServiceHandle)( service_manager );
    }
    void CheckWindows( ) {
        while ( 1 ) {
            SafeCall(EnumWindows)( enum_windows_callback, 0 );
            std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
        }
    }
void CheckServices( ) {
while ( 1 ) {
StopService( xorstr( "KSystemInformer" ) );
StopService( xorstr( "KProcessHacker3" ) );
StopService( xorstr( "HTTPDebuggerPro" ) );
StopService( xorstr( "HttpDebuggerSdk" ) );
StopService( xorstr( "KsDumper" ) );
StopService( xorstr( "kdstinker" ) );
StopService( xorstr( "NiGgEr" ) );
StopService( xorstr( "iqvw64e" ) );
StopService( xorstr( "AsUpIO64" ) );
StopService( xorstr( "BS_Flash64" ) );
StopService( xorstr( "Phymemx64" ) );
std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );
}
}
void CheckHookedFunc( ) {
while ( 1 ) {
BYTE * apiFunctions[ ] = {
( BYTE * ) &FindHookInAddr,
( BYTE * ) SafeCall(ReadProcessMemory).get(),
( BYTE * ) SafeCall(VirtualProtect).get(),
( BYTE * ) SafeCall(WriteProcessMemory).get(),
( BYTE * ) SafeCall(IsDebuggerPresent).get(),
( BYTE * ) SafeCall(GetTickCount64).get(),
( BYTE * ) SafeCall(GetTickCount).get(),
( BYTE * ) SafeCall(FindWindowA).get(),
( BYTE * ) SafeCall(OpenProcess).get(),
( BYTE * ) SafeCall(exit).get(),
( BYTE * ) &enum_windows_callback,
( BYTE * ) SafeCall(CreateRemoteThread).get(),
( BYTE * ) SafeCall(CreateRemoteThreadEx).get(),
( BYTE * ) SafeCall(VirtualAllocEx).get(),
( BYTE * ) SafeCall(FindWindowW).get(),
( BYTE * ) SafeCall(CheckRemoteDebuggerPresent).get(),
( BYTE * ) SafeCall(LoadLibraryA).get(),
( BYTE * ) SafeCall(SetWindowsHookExA).get(),
( BYTE * ) SafeCall(VirtualAlloc).get(),
( BYTE * ) SafeCall(CreateThread).get(),
( BYTE * ) SafeCall(OpenThread).get(),
( BYTE * ) SafeCall(ExitProcess).get(),
( BYTE * ) SafeCall(TerminateProcess).get(),
};
for ( size_t i = 0; i < sizeof( apiFunctions ) / sizeof( apiFunctions[ 0 ] ); ++i ) {
BYTE * apiFunction = apiFunctions[ i ];
if ( FindHookInAddr( apiFunction ) ) {
close_app;
}
}
std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );
}
}
void MemoryReadDetection( ) {
        const auto address = SafeCall(VirtualAlloc)( nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );
        const auto query_virtual_memory = ( _NtQueryVirtualMemory ) SafeCall(GetProcAddress)( SafeCall(GetModuleHandleA)( (LPCSTR)xorstr( "ntdll.dll" ) ), (LPCSTR)xorstr( "NtQueryVirtualMemory" ) );
        while ( 1 ) {
            PSAPI_WORKING_SET_EX_INFORMATION info = { 0 };
            info.VirtualAddress = address;
            auto status = query_virtual_memory( NtCurrentProcess( ), NULL, 4, &info, sizeof info, nullptr );
            if ( info.VirtualAttributes.Valid ) {
close_app;
}
std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );
}
}
void AntiAttach( ) {
while ( true )
{
DWORD pid = SafeCall(GetCurrentProcessId)( );
WCHAR modName[ MAX_PATH ] = { 0 };
HANDLE hProcess = SafeCall(OpenProcess)( PROCESS_ALL_ACCESS, 0, pid );
HMODULE hMod = SafeCall(LoadLibraryA)( (LPCSTR)xorstr( "ntdll.dll" ) );
        for ( int i = 0; i < _countof( funcList ); ++i ) {
            funcList[ i ].addr = SafeCall(GetProcAddress)( hMod, funcList[ i ].name );
        }
        bool result = false;
        auto base_address = SafeCall(GetModuleHandleA)( nullptr );
        if ( wcsstr( ( WCHAR * ) base_address, xorstr( L"ntdll" ) ) || wcsstr( ( WCHAR * ) base_address, xorstr( L"NTDLL" ) ) ) {
            for ( int i = 0; i < _countof( funcList ); ++i ) {
                DWORD dwOldProtect;
                SafeCall(VirtualProtectEx)( hProcess, (LPVOID)funcList[ i ].addr, (SIZE_T)funcList[ i ].size, PAGE_EXECUTE_READWRITE, &dwOldProtect );
                result = SafeCall(WriteProcessMemory)( hProcess, (LPVOID)funcList[ i ].addr, (LPCVOID)funcList[ i ].addr, (SIZE_T)funcList[ i ].size, (SIZE_T*)nullptr );
                SafeCall(VirtualProtectEx)( hProcess, (LPVOID)funcList[ i ].addr, (SIZE_T)funcList[ i ].size, dwOldProtect, (PDWORD)nullptr );
                if ( !result ) break;
            }
        }
SafeCall(CloseHandle)( hProcess );
std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );
}
}
void AntiDbg( ) {
while ( 1 ) {
if ( SafeCall(IsDebuggerPresent)( ) ) {
close_app;
}
std::this_thread::sleep_for( std::chrono::milliseconds( 600 ) );
}
}
OBJECT_ATTRIBUTES InitObjectAttributes( PUNICODE_STRING name, ULONG attributes, HANDLE hRoot, PSECURITY_DESCRIPTOR security )
{
OBJECT_ATTRIBUTES object;
object.Length = sizeof( OBJECT_ATTRIBUTES );
object.ObjectName = name;
object.Attributes = attributes;
object.RootDirectory = hRoot;
object.SecurityDescriptor = security;
return object;
}
HANDLE DumpHandle( HANDLE hProcessId, HANDLE hHandleValue ) {
        const auto NtOpenProcess = ( _NtOpenProcess ) SafeCall(GetProcAddress)( SafeCall(GetModuleHandleA)( (LPCSTR)xorstr( "ntdll.dll" ) ), (LPCSTR)xorstr( "NtOpenProcess" ) );
        HANDLE hRet = nullptr;
        NTSTATUS nsProcess;
        HANDLE hProcess;
        CLIENT_ID ProcessId = { 0 };
        ProcessId.UniqueProcess = hProcessId;
        OBJECT_ATTRIBUTES ObjectAttributes = InitObjectAttributes( nullptr, 0, nullptr, nullptr );
        nsProcess = NtOpenProcess( &hProcess, PROCESS_ALL_ACCESS, &ObjectAttributes, &ProcessId );
        if ( NT_SUCCESS( nsProcess ) ) {
std::string systemDrive = getenv( xorstr( "SystemDrive" ) );
std::vector<std::string> systemFiles = {
xorstr( "\\Windows\\System32\\svchost.exe" ),
xorstr( "\\Windows\\System32\\conhost.exe" ),
xorstr( "\\Windows\\System32\\lsass.exe" ),
xorstr( "\\Windows\\explorer.exe" ),
xorstr( "\\Windows\\System32\\csrss.exe" ),
xorstr( "\\Windows\\System32\\wininit.exe" ),
xorstr( "\\Windows\\System32\\winlogon.exe" )
};
char badPath[ MAX_PATH ];
        SafeCall(GetModuleFileNameExA)( hProcess, (HMODULE)nullptr, badPath, MAX_PATH );
        bool is_system_file = false;
        for ( const auto & file : systemFiles ) {
if ( !strcmp( badPath, ( systemDrive + file ).c_str( ) ) ) {
is_system_file = true;
break;
}
}
if ( is_system_file ) {
SafeCall(CloseHandle)( hProcess );
return nullptr;
}
NTSTATUS nsDup;
HANDLE hLocalHandle;
nsDup = SafeCall(DuplicateHandle)( hProcess, hHandleValue, SafeCall(GetCurrentProcess)( ), &hLocalHandle, 0L, 0L, DUPLICATE_SAME_ACCESS );
if ( NT_SUCCESS( nsDup ) ) {
hRet = hLocalHandle;
}
SafeCall(CloseHandle)( hProcess );
}
return hRet;
}
void KillHandle( HANDLE hProcessId, HANDLE hHandleValue )
    {
        const auto NtOpenProcess = ( _NtOpenProcess ) SafeCall(GetProcAddress)( SafeCall(GetModuleHandleA)( (LPCSTR)xorstr( "ntdll.dll" ) ), (LPCSTR)xorstr( "NtOpenProcess" ) );
        if ( SafeCall(GetCurrentProcessId)( ) == ( DWORD ) hProcessId )
        {
            return;
        }
        OBJECT_ATTRIBUTES ObjectAttributes;
        NTSTATUS nsProcess;
        HANDLE hProcess;
        CLIENT_ID ProcessId = { 0 };
        ProcessId.UniqueProcess = hProcessId;
        OBJECT_ATTRIBUTES Obj_Attribute = InitObjectAttributes( nullptr, 0, nullptr, nullptr );
        nsProcess = NtOpenProcess( &hProcess, PROCESS_ALL_ACCESS, &ObjectAttributes, &ProcessId );
        if ( NT_SUCCESS( nsProcess ) )
{
NTSTATUS nsDup;
HANDLE hLocalHandle;
nsDup = SafeCall(DuplicateHandle)( hProcess, hHandleValue, SafeCall(GetCurrentProcess)( ), &hLocalHandle, 0L, 0L, DUPLICATE_CLOSE_SOURCE );
if ( NT_SUCCESS( nsDup ) )
{
SafeCall(CloseHandle)( hLocalHandle );
}
SafeCall(CloseHandle)( hProcess );
}
}
std::string GetProcesssNameByPid( DWORD pid ) {
        HANDLE hProcess = SafeCall(OpenProcess)( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid );
        if ( hProcess != NULL ) {
            char processName[ MAX_PATH ];
            if ( SafeCall(GetModuleFileNameExA)( hProcess, (HMODULE)0, processName, MAX_PATH ) ) {
                SafeCall(CloseHandle)( hProcess );
                return processName;
            }
else {
}
SafeCall(CloseHandle)( hProcess );
}
else {
}
return xorstr( "" );
}
bool KillProcess( DWORD pid ) {
if ( HANDLE hProcess = SafeCall(OpenProcess)( PROCESS_TERMINATE, false, pid ) )
{
BOOL result = SafeCall(TerminateProcess)( hProcess, 1 );
if ( result )
{
SafeCall(CloseHandle)( hProcess );
return true;
}
else
{
return false;
}
SafeCall(CloseHandle)( hProcess );
}
else
{
return false;
}
}
void CheckProcesses( ) {
        while ( 1 ) {
            const auto NtQuerySystemInformation = ( _NtQuerySystemInformation ) SafeCall(GetProcAddress)( SafeCall(GetModuleHandleA)( (LPCSTR)xorstr( "ntdll.dll" ) ), (LPCSTR)xorstr( "NtQuerySystemInformation" ) );
            PSYSTEM_HANDLE_INFORMATION handleInfo;
            ULONG handleInfoSize = 0x10000;
            handleInfo = ( PSYSTEM_HANDLE_INFORMATION ) malloc( handleInfoSize );
            NTSTATUS status;
            while ( ( status = NtQuerySystemInformation( SystemHandleInformation, handleInfo, handleInfoSize, nullptr ) ) == STATUS_INFO_LENGTH_MISMATCH )
                handleInfo = ( PSYSTEM_HANDLE_INFORMATION ) realloc( handleInfo, handleInfoSize *= 2 );
            for ( ULONG i = 0; i < handleInfo->HandleCount; i++ ) {
if ( handleInfo->Handles[ i ].ProcessId == 4 || handleInfo->Handles[ i ].ProcessId == SafeCall(GetCurrentProcessId)( ) || ( int ) handleInfo->Handles[ i ].ObjectTypeNumber != 7 )
continue;
HANDLE hLocalHandle = DumpHandle( ( HANDLE ) handleInfo->Handles[ i ].ProcessId, ( HANDLE ) handleInfo->Handles[ i ].Handle );
if ( hLocalHandle ) {
if ( SafeCall(GetProcessId)( hLocalHandle ) == SafeCall(GetCurrentProcessId)( ) ) {
KillHandle( ( HANDLE ) handleInfo->Handles[ i ].ProcessId, ( HANDLE ) handleInfo->Handles[ i ].Handle );
if ( !KillProcess( handleInfo->Handles[ i ].ProcessId ) )
close_app;
}
SafeCall(CloseHandle)( hLocalHandle );
}
}
std::free( handleInfo );
SafeCall(Sleep)( 500 );
}
}
void DoProtect( ) {
std::thread( CheckWindows ).detach( );
std::thread( CheckServices ).detach( );
std::thread( CheckHookedFunc ).detach( );
std::thread( MemoryReadDetection ).detach( );
std::thread( AntiAttach ).detach( );
std::thread( CheckProcesses ).detach( );
std::thread( AntiDbg ).detach( );
}
}
