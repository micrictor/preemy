#include <Windows.h>
#include <detours.h>
#include <cstdio>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "detours.lib")

int ( WINAPI *orig_send )( SOCKET s, const char *buf, int len, int flags ) = send;
int WINAPI new_send( SOCKET s, const char* buf, int len, int flags );

BOOL WINAPI DllMain( HINSTANCE, DWORD dwReason, LPVOID )
{
	switch( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			// Initialize hooks
			DetourTransactionBegin();
            DetourUpdateThread( GetCurrentThread() );
            DetourAttach( &(PVOID &)send, new_send );

            if( DetourTransactionCommit() == NO_ERROR )
				MessageBoxA( NULL, "Preemy: send blocking module successfully injected", "Preemy", MB_OK | MB_ICONINFORMATION );
			else
				MessageBoxA( 0, "ERROR! Injection failed!", "ERROR", MB_OK | MB_ICONERROR );

			break;
		case DLL_PROCESS_DETACH:
			// Destroy hooks
			DetourTransactionBegin();
            DetourUpdateThread( GetCurrentThread() );
            DetourDetach( &(PVOID &)send, new_send );
            DetourTransactionCommit();
			break;
	}

	return true;
}

int WINAPI new_send( SOCKET s, const char* buf, int len, int flags )
{
	MessageBoxA( NULL, "Preemy: send() blocked", "Preemy", MB_OK | MB_ICONINFORMATION );
	return -1;
}