#include "Memory.h"

DWORD GetPID(const wchar_t* procName)
{
	DWORD PID = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry) == 1)
		{
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) {
					PID = procEntry.th32ProcessID;
					break;

				}
			} while (Process32Next(hSnap, &procEntry) == 1);
		}
	}
	CloseHandle(hSnap);
	return PID;
}


uintptr_t GetModule(DWORD PID, const wchar_t* modName) 
{
	uintptr_t baseAddress = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry) == 1)
		{
			do {
				if (!_wcsicmp (modEntry.szModule, modName)) 
				{
					baseAddress = (uintptr_t)modEntry.modBaseAddr;
					break;

				}
			} while (Module32Next(hSnap, &modEntry) == 1);
		}
	}
	CloseHandle(hSnap);
	return baseAddress;
}	


uintptr_t FindAddress(HANDLE hProc, std::vector<int> offsets, uintptr_t baseAddress)
{
	for (int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(hProc, (LPCVOID)baseAddress, &baseAddress, sizeof(baseAddress), NULL);
		baseAddress += offsets[i];
	}
	return baseAddress;
}