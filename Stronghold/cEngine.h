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
	uintptr_t Find_DMA_Address(HANDLE hProc, uintptr_t ptr);
	
	std::vector<int> value_return(int category);

	void hack_value(int category, std::string new_values[]);
	void save_to_process(std::string new_value, unsigned int address);

	void read_from_process(unsigned int Offset, std::vector<int>& arr_of_values);

private:
	const wchar_t* procName=L"Stronghold2.exe";
	const wchar_t* modName=L"Stronghold2.exe";

	DWORD ProcId;

	int number_of_fields = 12;

	HANDLE hProcess = 0;
	uintptr_t dynamicPtrBaseAddr;
	uintptr_t moduleBase;
	uintptr_t** Granary_adrr;
	uintptr_t** Armoury_adrr;
	uintptr_t** Stockpile_adrr;

	std::vector<unsigned int> StockPileOffsets={ 0xC04,0xC08,0xC0C,0xC24,0xC2C,0xC30,0xC14,0xC10,0xC1C,0xC28,0xC20,0xC18 }; // wood,stone,iron,tar,wool,clothes,flour,wheat,beer,candle,grapes,hops
	std::vector<unsigned int> GranaryOffsets={ 0xC58,0xC5C,0xC60,0xC64,0xC38,0xC3C,0xC44,0x48,0xC4C }; // apple,roll,cheese,meat,eel,goose,pig,vegetables,wine
	std::vector<unsigned int> ArmouryOffsets={ 0xC78,0xC7C,0xC80,0xC84,0xC88,0xC8C,0xC90,0xC94 }; // bow,crossbow,sword,mace,spear,pike,iron armour,leather armour

};

