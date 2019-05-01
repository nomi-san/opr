from ctypes import *
from ctypes.wintypes import *

class opr:

	PROCESS_ALL_ACCESS = 0x1FFFFF
	TH32CS_SNAPPROCESS = 0x000002
	MAX_PROCESSID = 0xffff # 0xffffffff
	MAX_PATH = 260

	class PROCESSENTRY32(Structure):
		_fields_ = [
			('dwSize',              DWORD),
			('cntUsage',            DWORD),
			('th32ProcessID',       DWORD),
			('th32DefaultHeapID',   POINTER(ULONG)),
			('th32ModuleID',        DWORD),
			('cntThreads',          DWORD),
			('th32ParentProcessID', DWORD),
			('pcPriClassBase',      LONG),
			('dwFlags',             DWORD),
			('szExeFile',           c_char * MAX_PATH)
		]
	#end

	def Clean(p = None):
		h = 0
		r = -1

		if (p == None):
			h = windll.kernel32.GetCurrentProcess()
		elif isinstance(p, int):
			if p < 0:
				h = windll.kernel32.GetCurrentProcess()
			else:
				h = windll.kernel32.OpenProcess(opr.PROCESS_ALL_ACCESS, 0, p)
			#end
		elif isinstance(p, str):
			e = opr.PROCESSENTRY32()
			e.dwSize = sizeof(e)

			s = windll.kernel32.CreateToolhelp32Snapshot(opr.TH32CS_SNAPPROCESS, 0)
			p = ("b'{0}'").format(p.lower())

			if windll.kernel32.Process32First(s, addressof(e)) == 1:
				while windll.kernel32.Process32Next(s, addressof(e)) == 1:
					if str(e.szExeFile).lower() == p:
						h = windll.kernel32.OpenProcess(opr.PROCESS_ALL_ACCESS, 0, e.th32ProcessID);
						break
					#end
				#end
			#end
		#end

		if (h != 0):
			windll.kernel32.SetProcessWorkingSetSizeEx(h, c_size_t(-1), c_size_t(-1), DWORD(0x0001));
			r = windll.psapi.EmptyWorkingSet(h);
			windll.kernel32.CloseHandle(h)
		#end

		return r
	#end

	def CleanAll():

		ids = (DWORD * opr.MAX_PROCESSID)()
		cid = DWORD()
		c = 0

		if windll.psapi.EnumProcesses(ids, sizeof(ids), addressof(cid)) == 1:
			r = int(cid.value/sizeof(DWORD))
			for i in range(0, r):
				if opr.Clean(ids[i]) == 1:
					c += 1
				#end
			#end
		#end

		return c
	#end
#end