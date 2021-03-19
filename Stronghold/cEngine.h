#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>




class cEngine
{
public:

	cEngine();
	~cEngine();

	DWORD Get_Process_Id(const wchar_t* procName);
	uintptr_t Get_Module_Address(DWORD procId, const wchar_t* modName);
	std::vector <uintptr_t> Find_DMA_Address(HANDLE hProc, uintptr_t ptr, unsigned int offsets[],int size);
	
	std::vector<int> value_return(int category);

	void hack_value(int category, std::string new_values[]);
	void save_to_process(std::string new_value, unsigned int address);

	void read_from_process(unsigned int Offset, std::vector<int>& arr_of_values);

private:
	const wchar_t* procName=L"Stronghold.exe";
	const wchar_t* modName=L"Stronghold.exe";

	DWORD ProcId;

	int number_of_fields = 8;

	HANDLE hProcess = 0;
	uintptr_t dynamicPtrBaseAddr;
	uintptr_t moduleBase;
	uintptr_t** Granary_adrr;
	uintptr_t** Armoury_adrr;
	uintptr_t** Stockpile_adrr;

	std::vector<unsigned int> StockPileOffsets={ 0x0076A618,0x0076A620,0x0076A628,0x0076A62C,0x0076A650 }; // wood,stone,iron,tar,flour
	std::vector<unsigned int> GranaryOffsets={ 0x0076A638,0x0076A61C,0x0076A644,0x0076A640,0x0076A648,0x0076A634,0x0076A63C }; // roll,hop,apple,meat,beer,wheat,cheese
	std::vector<unsigned int> ArmouryOffsets={ 0x0076A654,0x0076A65C,0x0076A664,0x0076A658,0x0076A660,0x0076A668,0x0076A66C,0x0076A670 }; // bow,spear,baton,crossbow, halberd, sword, leather armor, iron armor

};

