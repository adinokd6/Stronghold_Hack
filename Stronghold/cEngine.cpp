#include "cEngine.h"




cEngine::cEngine()
{
	procId = Get_Process_Id(procName);
	moduleBase = Get_Module_Address(modName);

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	dynamicPtrBaseAddr = moduleBase;
}

cEngine::~cEngine()
{
}

DWORD cEngine::Get_Process_Id(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}


			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);

	return procId;
}

uintptr_t cEngine::Get_Module_Address(DWORD procId, const wchar_t* modName)
{
	DWORD modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}


			} while (Module32Next(hSnap, &modEntry));
		}
	}

	CloseHandle(hSnap);

	return modBaseAddr;
}

uintptr_t cEngine::Find_DMA_Address(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0;i < offsets.size();++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(uintptr_t), 0);
	}


	return addr;
}

int cEngine::value_return(std::string name_of_category)
{
	int item_Value[7] = {1,2,3,4,5,6,7};
	ReadProcessMemory(hProcess, (BYTE*)item_Addr, &item_Value[i], sizeof(item_Value[i]), nullptr);


	return 0;
}

void cEngine::hack_value(int tab[])
{
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
}
