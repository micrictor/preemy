#include <Windows.h>
#include <detours.h>
#include <stdlib.h>
#include "main.h"
#include "inject_dialog.h"
#include <cstdio>

#pragma comment(lib, "detours.lib")
#pragma comment (lib, "user32.lib") // I really should put these both in project prefs. *shrug*

int ( __cdecl *orig_rand )(  ) = rand;
int __cdecl new_rand( );

BOOL WINAPI DllMain( HINSTANCE, DWORD dwReason, LPVOID )
{
	switch( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			// Initialize hooks
			DetourTransactionBegin();
            DetourUpdateThread( GetCurrentThread() );
            DetourAttach( &(PVOID &)rand, new_rand );

            if( DetourTransactionCommit() == NO_ERROR )
				gcnew rand_module::inject_dialog();
			else
				MessageBoxA( 0, "ERROR! Injection failed!", "ERROR", MB_OK | MB_ICONERROR );

			break;
		case DLL_PROCESS_DETACH:
			// Destroy hooks
			DetourTransactionBegin();
            DetourUpdateThread( GetCurrentThread() );
            DetourDetach( &(PVOID &)rand, new_rand );
            DetourTransactionCommit();
			break;
	}

	return true;
}

int __cdecl new_rand( )
{
	MessageBoxA( NULL, "Preemy: rand() intercepted", "Preemy", MB_OK | MB_ICONINFORMATION );
	return g_desired_return;
}