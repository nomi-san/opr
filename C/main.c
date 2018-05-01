#include <windows.h>

typedef BOOL (__stdcall * EmptyWorkingSet)(HANDLE);

int main() {
	HMODULE module = LoadLibraryA("psapi.dll");
	FARPROC proc = GetProcAddress(module, "EmptyWorkingSet"); // cho ai ghét thêm psapi.lib vào compiler
	for (int i = 0; i <= 32768; ++i) {
		HANDLE handle = OpenProcess(0x1F0FFF, false, i);
		if (handle) {
			((EmptyWorkingSet)(proc))(handle);
			CloseHandle(handle); 
		}
	}
	return 1;
}