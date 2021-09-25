#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD GetPID(const wchar_t* procName);

uintptr_t GetModule(DWORD PID, const wchar_t* modName);

uintptr_t FindAddress(HANDLE hProc, std::vector<int>, uintptr_t baseAddress);



