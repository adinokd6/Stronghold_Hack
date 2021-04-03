#include "cEngine.h"

#define STOCKPILE 0
#define GRANARY 3 //because its 3 less items in granary and kitchen
#define ARMOURY 4 //same case as up


cEngine::cEngine()
{
	ProcId = Get_Process_Id(procName);
	

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcId);
	moduleBase = Get_Module_Address(ProcId, modName);

	moduleBase += 0x11CBFB4;
	dynamicPtrBaseAddr = Find_DMA_Address(hProcess,moduleBase);

	
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

uintptr_t cEngine::Find_DMA_Address(HANDLE hProc, uintptr_t ptr)
{
	uintptr_t tmp_addr;
	ReadProcessMemory(hProc, (BYTE*)ptr, &tmp_addr, sizeof(uintptr_t), 0);

	return tmp_addr;
}

std::vector <int> cEngine::value_return(int category)
{
	std::vector <int> tmp_arr_of_values;

	std::vector<unsigned int> tmp_offsets;

	if (category == GRANARY)
	{
		tmp_offsets = GranaryOffsets;
	}
	else if (category == ARMOURY)
	{
		tmp_offsets = ArmouryOffsets;
	}
	else
	{
		tmp_offsets = StockPileOffsets;
	}

	for (int i = 0;i < tmp_offsets.size();i++)
	{
		read_from_process(tmp_offsets[i], tmp_arr_of_values);
	}

	return tmp_arr_of_values;
}


void cEngine::read_from_process(unsigned int Offset,std::vector<int>& arr_of_values)
{
	uintptr_t tmp_addr = dynamicPtrBaseAddr+ Offset;
	int readed_value = 0;
	ReadProcessMemory(hProcess, (BYTE*)tmp_addr, &readed_value, sizeof(readed_value), nullptr);
	arr_of_values.push_back(readed_value);
}

void cEngine::hack_value(int category, std::string new_values[])
{
	std::vector<unsigned int> tmp_offsets;

	if (category == GRANARY)
	{
		tmp_offsets = GranaryOffsets;
	}
	else if (category == ARMOURY)
	{
		tmp_offsets = ArmouryOffsets;
	}
	else
	{
		tmp_offsets = StockPileOffsets;
	}

	for (int i = 0;i < number_of_fields - category;i++)
	{
		save_to_process(new_values[i],tmp_offsets[i]);
	}
}

void cEngine::save_to_process(std::string new_value, unsigned int address)
{
	if (new_value == "null")
	{

	}
	else
	{
		uintptr_t tmp_addr = dynamicPtrBaseAddr + address;
		int int_new_value = std::stoi(new_value);
		WriteProcessMemory(hProcess, (BYTE*)tmp_addr, &int_new_value, sizeof(int_new_value), nullptr);
	}
}




