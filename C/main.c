#include <windows.h>

typedef BOOL (__stdcall * EmptyWorkingSet)(HANDLE);
typedef BOOL (__stdcall * _SetProcessWorkingSetSizeEx)(
  HANDLE hProcess,
  SIZE_T dwMinimumWorkingSetSize,
  SIZE_T dwMaximumWorkingSetSize,
  DWORD  Flags
);

int main() {
	HMODULE module = LoadLibraryA("psapi.dll");
	HMODULE module2 = LoadLibraryA("kernel32.dll");
	FARPROC proc = GetProcAddress(module, "EmptyWorkingSet"); // cho ai ghét thêm psapi.lib vào compiler
	FARPROC proc2 = GetProcAddress(module2, "SetProcessWorkingSetSizeEx");
	for (int i = 0; i <= 32768; ++i) {
		HANDLE handle = OpenProcess(0x1F0FFF, 0, i);
		if (handle) {
			((_SetProcessWorkingSetSizeEx)(proc2))(handle, -1, -1, 0x1);
			((EmptyWorkingSet)(proc))(handle);
			CloseHandle(handle); 
		}
	}

	return 1;
}
