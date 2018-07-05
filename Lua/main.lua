require "module"

for pid = 1, 32768 do
	handle = OpenProcess(0x1F0FFF, false, pid)
	if handle then
		EmptyWorkingSet(handle)
		CloseHandle(handle)
	end
end
