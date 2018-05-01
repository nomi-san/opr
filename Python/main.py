from ctypes import *
from ctypes.wintypes import *

def main():
	for pid in range(0, 32768):
		handle = windll.kernel32.OpenProcess(DWORD(0x1F0FFF), False, DWORD(pid))
		if handle != 0:
			windll.kernel32.SetProcessWorkingSetSizeEx(handle, c_size_t(-1), c_size_t(-1), DWORD(0x1))
			windll.psapi.EmptyWorkingSet(handle)
			windll.kernel32.CloseHandle(handle)

if __name__ == "__main__":
	main()