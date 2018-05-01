require "ffi"

module WinAPI # f*ck!!! module phải in hoa chữ cái đầu =]]
	extend FFI::Library
	ffi_lib 'kernel32'
	attach_function :OpenProcess, :OpenProcess, [ :uint, :bool, :uint ], :pointer
	attach_function :CloseHandle, :CloseHandle, [ :pointer ], :bool
	attach_function :SetProcessWorkingSetSizeEx, :SetProcessWorkingSetSizeEx, [ :pointer, :int, :int, :uint], :bool


	ffi_lib 'psapi'
	attach_function :EmptyWorkingSet, :EmptyWorkingSet, [ :pointer ], :bool
end

pid = 5
until pid >= 32768
	handle = WinAPI.OpenProcess(0x1F0FFF, false, pid)
		if handle
			WinAPI.SetProcessWorkingSetSizeEx(handle, -1, -1, 0x1)
			WinAPI.EmptyWorkingSet(handle)
			WinAPI.CloseHandle(handle)
		end
	pid += 1
end