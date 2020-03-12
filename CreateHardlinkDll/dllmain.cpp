// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

int createHardLink(_TCHAR* linkName, _TCHAR* target);

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
		MessageBox(NULL, L"rundll32.exe <DLL>,Copy <linkname> <target>\n", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	linkname = argv[2];
	target = argv[3];

	createHardLink(linkname, target);
}


int createHardLink(_TCHAR* linkName, _TCHAR* target)
{
	if (!CreateNativeHardlink(linkName, target))
	{
		std::wstring error = GetErrorMessage();
		MessageBox(NULL, error.c_str(), L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	return 0;
}