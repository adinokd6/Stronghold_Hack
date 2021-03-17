#include "cEngine.h"

#define GRANARY 1
#define ARMOURY 2
#define STOCKPILE 3


cEngine::cEngine()
{
	ProcId = Get_Process_Id(procName);
	moduleBase = Get_Module_Address(ProcId,modName);

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcId);

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

std::vector <uintptr_t> cEngine::Find_DMA_Address(HANDLE hProc, uintptr_t ptr, unsigned int offsets[],int size)
{
	std::vector <uintptr_t> addr;
	uintptr_t tmp_addr;

	for (unsigned int i = 0;i < size;++i)
	{
		ReadProcessMemory(hProc, (BYTE*)tmp_addr, &tmp_addr, sizeof(uintptr_t), 0);

		addr.push_back(tmp_addr);
	}


	return addr;
}

std::vector <int> cEngine::value_return(int category)
{
	
	return read_from_process(category);

}


void cEngine::hack_value(unsigned int tab_addresses[], int category,int new_values[])
{
	if (category == GRANARY)
	{
		for (int i = 0;i < 7;i++)
		{
			save_to_process(new_values[i], tab_addresses[i]);
		}
	}
	else if (category == STOCKPILE)
	{
		for (int i = 0;i < 8;i++)
		{
			save_to_process(new_values[i], tab_addresses[i]);
		}
	}
	else
	{
		for (int i = 0;i < 5;i++)
		{
			save_to_process(new_values[i], tab_addresses[i]);
		}
	}
	
}

void cEngine::save_to_process(int new_value, uintptr_t address)
{
	uintptr_t tmp_addr = address + moduleBase;
	WriteProcessMemory(hProcess, (BYTE*)tmp_addr, &new_value, sizeof(new_value), nullptr);
}

std::vector<int> cEngine::read_from_process(int category)
{
	if (category == GRANARY)
	{
		std::vector <int> tmp_tab = {0,0,0,0,0,0,0};
		for (int i = 0;i < 7;i++)
		{
			uintptr_t tmp_addr = moduleBase + GranaryOffsets[i];
			ReadProcessMemory(hProcess, (BYTE*)tmp_addr, &tmp_tab[i], sizeof(tmp_tab[i]), nullptr);
		}
		
		return tmp_tab;

	}
	else if (category == ARMOURY)
	{
		std::vector <int> tmp_tab = {0,0,0,0,0,0,0,0};
		for (int i = 0;i < 8;i++)
		{
			uintptr_t tmp_addr = moduleBase + ArmouryOffsets[i];
			ReadProcessMemory(hProcess, (BYTE*)tmp_addr, &tmp_tab[i], sizeof(tmp_tab[i]), nullptr);
		}
		return tmp_tab;

	}
	else
	{
		std::vector <int> tmp_tab = { 0,0,0,0,0 };
		for (int i = 0;i < 5;i++)
		{
			uintptr_t tmp_addr = moduleBase + StockPileOffsets[i];
			ReadProcessMemory(hProcess, (BYTE*)tmp_addr, &tmp_tab[i], sizeof(tmp_tab[i]), nullptr);
		}
		return tmp_tab;
	}

	

}



