// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <FileSymlink.h>

int createSymlink(_TCHAR* linkName, _TCHAR* target);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void Link(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {

	int argc;
	LPWSTR* argv;
	LPWSTR target;
	LPWSTR	linkname;

	argv = CommandLineToArgvW(GetCommandLine(), &argc);
	if (argc != 4) {
		MessageBox(NULL, L"rundll32.exe <DLL>,Link <linkname> <target>\n", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	linkname = argv[2];
	target = argv[3];

	createSymlink(linkname, target);
}

int createSymlink(_TCHAR* linkname, _TCHAR* target_p)
{
	LPCWSTR symlink = linkname;
	LPCWSTR target = target_p;
	LPCWSTR baseobjdir = nullptr;

	FileSymlink sl(false);

	if (sl.CreateSymlink(symlink, target, baseobjdir))
	{
		int msgboxID = MessageBox(NULL, L"Close this prompt to release the symlink.", L"Release Symlink", MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Error during symlink creation.", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}
	return 0;
}