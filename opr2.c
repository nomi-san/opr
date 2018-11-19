#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef BOOL(__stdcall * EWS)(HANDLE);
typedef BOOL(__stdcall * SPWSSE)(
		HANDLE hProcess,
		SIZE_T dwMinimumWorkingSetSize,
		SIZE_T dwMaximumWorkingSetSize,
		DWORD  Flags
	);

int main(int argc, char const *argv[])
{
	DWORD count = 0, time = 0;
	char buf[100];

	printf("Enter your time (example '3600' for 3600s):\n");
	gets_s(buf, 100);

	time = atoi(buf);
	if (time < 300) {
		printf("Your time is %ds, it be set to 300s (minimum).\nPress Ctrl+C to break.\n", time);
		time = 300;
	}
	else
		printf("Your time is %ds.\nPress Ctrl+C to break.\n", time);
	
	fflush(stdout);

	HMODULE psapi = LoadLibraryA("psapi.dll");
	HMODULE kernel32 = LoadLibraryA("kernel32.dll");
	EWS ews = (EWS)GetProcAddress(psapi, "EmptyWorkingSet");
	SPWSSE spwsse = (SPWSSE)GetProcAddress(kernel32, "SetProcessWorkingSetSizeEx");

	while (1) {
		count++;
		printf("-> cleaning [%d]\n", count);
		fflush(stdout);
		for (int i = 0; i <= 32768; i++) {
			HANDLE handle = OpenProcess(0x1F0FFF, 0, i);
			if (handle) {
				spwsse(handle, -1, -1, 0x1);
				ews(handle);
				CloseHandle(handle);
			}
		}
		Sleep(time * 1000);
	}

	FreeLibrary(psapi);
	FreeLibrary(kernel32);

	return 0;
}