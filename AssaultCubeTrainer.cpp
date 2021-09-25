#include "Memory.h"


int main()
{
	//Getting Process ID
	DWORD PID = GetPID(L"ac_client.exe");
	//Error check
	if (PID == NULL) {
		std::cout << "Process 'ac_client.exe' Not Found. " << std::endl;
		return EXIT_FAILURE;
		system("pause");
	}
	//Getting ModuleBaseAddress
	uintptr_t ModuleAddress = GetModule(PID, L"ac_client.exe");
	if (ModuleAddress == NULL) {
		std::cout << "ModuleAddress Failed. " << std::endl;
		return EXIT_FAILURE;
		system("pause");
	}
	//Opening Handle to the Process
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	
	uintptr_t playerBase = ModuleAddress + 0x00109B74;

	uintptr_t playerAddress = FindAddress(hProc, { 0 }, playerBase);
	//Offsets
	uintptr_t ARammo = playerAddress + 0x150;
	uintptr_t ARammoLeft = playerAddress + 0x128;
	uintptr_t pistolAmmo = playerAddress + 0x13C;
	uintptr_t pistolammoLeft = playerAddress + 0x114;
	uintptr_t Health = playerAddress + 0xF8;
	uintptr_t Armour = playerAddress + 0xFC;
	uintptr_t arRapidfire = playerAddress + 0x178;
	uintptr_t nadeAmmo = playerAddress + 0x158;
	uintptr_t nadeAnimation = playerAddress + 0x180;

	int memoryRead = NULL;
	//Values we want to write
	int ARammoNew = 999;
	int pistolammoNew = 999;
	int nadeAmmoNew = 999;
	int HealthNew = 999;
	int ArmourNew = 999;
	int arRapidfireNew = 0;
	int nadeRapidFire = 0;

	bool arammo = false;
	bool pistolammo = false;
	bool nadeammo = false;
	bool health = false;
	bool armour = false;
	bool rapidfire = false;

	//Console
	std::cout << "\nWELCOME TO ASSAULT CUBE TRAINER BY @STAIINLESS\n\n\n";
	std::cout << "F4 == ACTIVATE/DEACTIVATE RAPIDFIRE (NADES & AR)\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F5 == ACTIVATE/DEACTIVATE UNLIMITED AR AMMO\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F6 == ACTIVATE/DEACTIVATE UNLIMITED PISTOL AMMO\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F7 == ACTIVATE/DEACTIVATE UNLIMITED HEALTH\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F8 == ACTIVATE/DEACTIVATE UNLIMITED ARMOUR\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F12 == ACTIVATE/DEACTIVATE UNLIMITED GERNADES\n" << std::endl;
	std::cout << "---------------------------------------------------\n" << std::endl;
	std::cout << "F2 == EXIT TRAINER" << std::endl;


//Hack Loop 
	while (true)
	{
		if (GetAsyncKeyState(VK_F4))
		{
			rapidfire = !rapidfire;
			if (rapidfire) std::cout << "RAPIDFIRE IS ACTIVE." << std::endl;
			else std::cout << "RAPIDFIRE IN INACTIVE." << std::endl;
			Sleep(150);
		}
		if (rapidfire) 
		{
			bool wpm = WriteProcessMemory(hProc, (LPVOID)arRapidfire, &arRapidfireNew, sizeof(arRapidfire), NULL);
			Sleep(5);
			wpm = WriteProcessMemory(hProc, (LPVOID)nadeAnimation, &nadeRapidFire, sizeof(nadeAnimation), NULL);
			if (wpm == NULL) 
			{
				std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
				return EXIT_FAILURE;
				system("pause");
			}
		}
		if (GetAsyncKeyState(VK_F5))
		{
			arammo = !arammo;
			bool rpm = ReadProcessMemory(hProc, (LPCVOID)ARammo, &memoryRead, sizeof(ARammo), NULL);
			if (rpm == NULL)
			{
				std::cout << "ReadProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
				return EXIT_FAILURE;
				system("pause");
			}
			std::cout << "\nCurrent AR AMMO = " << memoryRead << std::endl;
			Sleep(150);
		}
			if (arammo)
			{
				bool wpm = WriteProcessMemory(hProc, (LPVOID)ARammo, &ARammoNew, sizeof(ARammo), NULL);
				Sleep(5);
				if (wpm == NULL)
				{
					std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
			}
		

			if (GetAsyncKeyState(VK_F6))
			{
				pistolammo = !pistolammo;
				bool rpm = ReadProcessMemory(hProc, (LPCVOID)pistolAmmo, &memoryRead, sizeof(pistolAmmo), NULL);
				if (rpm == NULL)
				{
					std::cout << "ReadProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
				std::cout << "\nCurrent PISTOL AMMO = " << memoryRead << std::endl;
				Sleep(150);
			}
			if (pistolammo)
			{
				bool wpm = WriteProcessMemory(hProc, (LPVOID)pistolAmmo, &pistolammoNew, sizeof(pistolAmmo), NULL);
				Sleep(5);
				if (wpm == NULL)
				{
					std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
			}

			if (GetAsyncKeyState(VK_F7))
			{
				health = !health;
				bool rpm = ReadProcessMemory(hProc, (LPCVOID)Health, &memoryRead, sizeof(Health), NULL);
				if (rpm == NULL)
				{
					std::cout << "ReadProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
				std::cout << "\nCurrent HEALTH = " << memoryRead << std::endl;
				Sleep(150);
			}
			if (health)
			{
				bool wpm = WriteProcessMemory(hProc, (LPVOID)Health, &HealthNew, sizeof(Health), NULL);
				Sleep(5);
				if (wpm == NULL)
				{
					std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
			}
		
			if (GetAsyncKeyState(VK_F8))
			{
				armour = !armour;
				bool rpm = ReadProcessMemory(hProc, (LPCVOID)Armour, &memoryRead, sizeof(Armour), NULL);
				if (rpm == NULL)
				{
					std::cout << "ReadProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
				std::cout << "\nCurrent Armour Value = " << memoryRead << std::endl;
				Sleep(150);
			}
			if (armour)
			{
				bool wpm = WriteProcessMemory(hProc, (LPVOID)Armour, &ArmourNew, sizeof(Armour), NULL);
				Sleep(5);
				if (wpm == NULL)
				{
					std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
			}

			if (GetAsyncKeyState(VK_F12))
			{
				nadeammo = !nadeammo;
				bool rpm = ReadProcessMemory(hProc, (LPCVOID)nadeAmmo, &memoryRead, sizeof(nadeAmmo), NULL);
				if (rpm == NULL)
				{
					std::cout << "ReadProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
				std::cout << "Current Gernades = " << memoryRead << std::endl;
				Sleep(150);
			}
			if (nadeammo)
			{
				bool wpm = WriteProcessMemory(hProc, (LPVOID)nadeAmmo, &nadeAmmoNew, sizeof(nadeAmmo), NULL);
				Sleep(5);
				if (wpm == NULL)
				{
					std::cout << "WriteProcessMemory Failed. Last Error = " << std::dec << GetLastError() << std::endl;
					return EXIT_FAILURE;
					system("pause");
				}
			}

			if (GetAsyncKeyState(VK_F2)) {
				break;
			}

	}
	CloseHandle(hProc);
}

