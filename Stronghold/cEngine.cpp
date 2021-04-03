#include "cEngine.h"

#define STOCKPILE 0
#define GRANARY 3 //because its 3 less items in granary and kitchen
#define ARMOURY 4 //same case as up
#define STEAM 1


cEngine::cEngine()
{

	ProcId = Get_Process_Id(procName);
	

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcId);
	moduleBase = Get_Module_Address(ProcId, modName);

	
}

cEngine::~cEngine()
{
}

void cEngine::Chose_version(int given_version)
{
	version = given_version;
}

void cEngine::Chose_offsets()
{
	if (version == STEAM)
	{
		unsigned int tmp_stockpile[12] = { 0xf60,0xf64,0xf68,0xf80,0xf88,0xf8c,0xf70,0xf6c,0xf78,0xf84,0xf7c,0xf74 }; // wood,stone,iron,tar,wool,clothes,flour,wheat,beer,candle,grapes,hops
		unsigned int tmp_granary[9] = { 0xfb4,0xfb8,0xfbc,0xfc0,0xf94,0xf98,0xfa0,0xfa4,0xfa8 }; // apple,roll,cheese,meat,eel,goose,pig,vegetables,wine
		unsigned int tmp_armoury[8]= { 0xfd4,0xfd8,0xfdc,0xfe0,0xfe4,0xfe8,0xfec,0xff0 }; // bow,crossbow,sword,mace,spear,pike,iron armour,leather armour
		moduleBase += 0x6E8C60;
		Copy_to_main_offsets(tmp_stockpile, tmp_granary, tmp_armoury);
	}
	else
	{
		unsigned int tmp_stockpile[12]= { 0xC04,0xC08,0xC0C,0xC24,0xC2C,0xC30,0xC14,0xC10,0xC1C,0xC28,0xC20,0xC18 }; // wood,stone,iron,tar,wool,clothes,flour,wheat,beer,candle,grapes,hops
		unsigned int tmp_granary[9] = { 0xC58,0xC5C,0xC60,0xC64,0xC38,0xC3C,0xC44,0x48,0xC4C }; // apple,roll,cheese,meat,eel,goose,pig,vegetables,wine
		unsigned int tmp_armoury[8] = { 0xC78,0xC7C,0xC80,0xC84,0xC88,0xC8C,0xC90,0xC94 }; // bow,crossbow,sword,mace,spear,pike,iron armour,leather armour
		moduleBase += 0x11CBFB4;
		Copy_to_main_offsets(tmp_stockpile, tmp_granary, tmp_armoury);
	}
	dynamicPtrBaseAddr = Find_DMA_Address(hProcess, moduleBase);

	
	
}

void cEngine::Copy_to_main_offsets(unsigned int to_stockpile[], unsigned int to_granary[], unsigned int to_armoury[])
{
	StockPileOffsets.insert(StockPileOffsets.begin(), to_stockpile, to_stockpile + 12);
	GranaryOffsets.insert(GranaryOffsets.begin(), to_granary, to_granary + 9);
	ArmouryOffsets.insert(ArmouryOffsets.begin(), to_armoury, to_armoury + 8);
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




