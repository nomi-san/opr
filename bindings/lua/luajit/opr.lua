local ffi = require('ffi')

ffi.cdef[[
typedef void *HANDLE;
typedef unsigned long DWORD;

HANDLE __stdcall GetCurrentProcess();
HANDLE __stdcall OpenProcess(DWORD, int, DWORD);

int __stdcall CloseHandle(HANDLE);
int __stdcall SetProcessWorkingSetSizeEx(HANDLE, size_t, size_t, DWORD);

typedef struct {
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;
    size_t  th32DefaultHeapID;
    DWORD   th32ModuleID;
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;
    long    pcPriClassBase;
    DWORD   dwFlags;
    char    szExeFile[260];
} PROCESSENTRY32;

int __stdcall Process32First(HANDLE, PROCESSENTRY32*);
int __stdcall Process32Next(HANDLE, PROCESSENTRY32*);

HANDLE __stdcall CreateToolhelp32Snapshot(DWORD, DWORD);
]]

ffi.cdef[[
int __stdcall K32EmptyWorkingSet(HANDLE);
int __stdcall K32EnumProcesses(DWORD*, DWORD, DWORD*);
]]

local M = {}

local MAX_PROCESSID = 0xffff -- 0xffffffff
local TH32CS_SNAPPROCESS = 0x000002
local PROCESS_ALL_ACCESS = 0x1fffff

local NULL = ffi.new('void*')
local DWORD_MAX = ffi.new('DWORD[1]', -1)[0]

local function isValid(ptr)
	if not ptr then return false end
	return ffi.cast('void*', ptr) ~= NULL
end

function M.Clean(p)

	local h, r = nil, 0

	if type(p) == 'number' then

		if p < 0 then
			h = ffi.C.GetCurrentProcess()
		else
			h = ffi.C.OpenProcess(PROCESS_ALL_ACCESS, 0, p)
		end

		if isValid(h) then
			ffi.C.SetProcessWorkingSetSizeEx(h, DWORD_MAX, DWORD_MAX, 0x1)
			r = ffi.C.K32EmptyWorkingSet(h)
			ffi.C.CloseHandle(h)
		else
			return -1
		end

	elseif type(p) == 'string' then

		local e, pe, s
		e = ffi.new('PROCESSENTRY32')
		e.dwSize = ffi.sizeof(e)
		pe = ffi.cast('PROCESSENTRY32*', e)

		r = -1
		p = string.lower(p)
		s = ffi.C.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)

		if ffi.C.Process32First(s, pe) == 1 then
			while ffi.C.Process32Next(s, pe) == 1 do
				if string.lower(ffi.string(e.szExeFile)) == p then
					h = ffi.C.OpenProcess(PROCESS_ALL_ACCESS, 0, e.th32ProcessID)
					if isValid(h) then
						ffi.C.SetProcessWorkingSetSizeEx(h, DWORD_MAX, DWORD_MAX, 0x1)
						r = ffi.C.K32EmptyWorkingSet(h)
						ffi.C.CloseHandle(h)
					end
				end
			end
		end

	end

	return r
end

function M.CleanAll()

	local ids = ffi.new('DWORD['..tostring(MAX_PROCESSID)..']')
	local cid = ffi.new('DWORD[1]')

	ffi.C.K32EnumProcesses(ids, MAX_PROCESSID, cid)

	local count = 0

	for i=0,((tonumber(cid[0]) / ffi.sizeof('DWORD')) - 1) do
		if M.Clean(ids[i]) == 1 then
			count = count + 1
		end
	end

	return count
end

return M