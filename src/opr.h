#ifndef _OPR_HEADER_H
#define _OPR_HEADER_H
#pragma once

#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

#ifdef _MSC_VER
#pragma comment(lib, "psapi.lib")
#endif

// for building dll/dynamic library
#if defined(OPR_EXPORTS) || defined(BUILD_DLL) || defined(BUILD_LIB)
#define OPR_API __declspec(dllexport)
#else
#define OPR_API
#endif

#ifndef MAX_PROCESSID
#define MAX_PROCESSID 0xffff // default: MAXDWORD 0xffffffff
#endif

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport)
BOOL __stdcall SetProcessWorkingSetSizeEx(HANDLE, SIZE_T, SIZE_T, DWORD);
__declspec(dllimport)
DWORD __stdcall GetProcessId(HANDLE);

OPR_API
static int opr_Clean(int processId)
{
	HANDLE hProcess = NULL;
	if (processId < 0) {
		hProcess = GetCurrentProcess();
	}
	else {
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	}

	int ret = 0;
	if (hProcess != NULL) {
		SetProcessWorkingSetSizeEx(hProcess, -1, -1, 0x0001);
		ret = EmptyWorkingSet(hProcess);
		CloseHandle(hProcess);
	}
	else {
		return -1;
	}
	
	return ret;
}

OPR_API
static int opr_CleanByHandle(HANDLE processHandle)
{
	if (processHandle == NULL)
	{
		return opr_Clean(-1);
	}

	DWORD id = GetProcessId(processHandle);
	return opr_Clean(id);
}

OPR_API
static int opr_CleanByName(const char *processName)
{
#undef PROCESSENTRY32
#undef Process32First
#undef Process32Next

	if (processName == NULL)
	{
		return opr_Clean(-1);
	}

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	int ret = -1;
	if (Process32First(snapshot, &entry) == 1) {
		while (Process32Next(snapshot, &entry) == 1) {
			if (stricmp(entry.szExeFile, processName) == 0) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, entry.th32ProcessID);
				if (hProcess != NULL) {
					SetProcessWorkingSetSizeEx(hProcess, -1, -1, 0x0001);
					ret = EmptyWorkingSet(hProcess);
					CloseHandle(hProcess);
				}
			}
		}
	}

	return ret;
}

OPR_API
static int opr_CleanAll()
{
	DWORD ids[MAX_PROCESSID], cid;
	int count = 0;

	if (EnumProcesses(ids, MAX_PROCESSID, &cid) != 0) {
		int range = cid / sizeof(DWORD);
		for (int i = 0; i < range; i++) {
			if (opr_Clean(ids[i]) != 0) {
				count++;
			}
		}
	}

	return count;
}

#ifdef __cplusplus
}

namespace opr {

	int Clean(int processId = -1)
	{
		return opr_Clean(processId);
	}

	int Clean(HANDLE processHandle = 0)
	{
		return opr_CleanByHandle(processHandle);
	}

	int Clean(const char *processName = 0)
	{
		return opr_CleanByName(processName);
	}

	int CleanAll()
	{
		return opr_CleanAll();
	}

}

#endif

#endif