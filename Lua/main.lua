require "module"

for pid = 1, 32768 do
	handle = OpenProcess(0x1F0FFF, false, pid)
	if handle then
		SetProcessWorkingSetSizeEx(handle, -1, -1, 0x1)
		EmptyWorkingSet(handle)
		CloseHandle(handle)
	end
end