require "module"

for pid = 0, 32768 do
	handle = OpenProcess(0x1F0FFF, false, pid)
	if handle then
		EmptyWorkingSet(handle)
		CloseHandle(handle)
	end
end
