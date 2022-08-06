#include "Memory.h"

#include "Printa.h"
#include "Xorstr.h"


uintptr_t GetModuleBaseAddress(const char* modName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) 
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	return NULL;
}


void Attach()
{
	window = FindWindowA(NULL, xorstr("AssaultCube"));		   // Window of prosses/game
	GetWindowThreadProcessId(window, &procId);				   // Getting 
	Base = GetModuleBaseAddress(xorstr("ac_client.exe"));	   // Base of the game
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);  // Giving rights to Read and Write

	while (window == NULL)
	{
		Printa::Loading("Please open Game");
		while (window == NULL)
		{

			GameOpen = false;
		}
	}
	std::cout << std::endl;

	Printa::OK("Found game!");

	Printa::Endl();

	Printa::PrintCol(" Window ", LIGHTCYAN);
	Printa::Arrow(BLUE);
	Printa::SetWhite();
	std::cout << "0x" << window << std::endl;

	Printa::PrintCol(" Base ", LIGHTCYAN);
	Printa::Arrow(BLUE);
	Printa::SetWhite();
	std::cout << "0x" << Base << std::endl;

	GameOpen = true;

}




