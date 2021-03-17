#pragma once

#include <iostream>
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
	uintptr_t Find_DMA_Address(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	
	int value_return(int category);

	void hack_value(int tab[],int category);

private:
	const wchar_t* procName=L"Stronghold.exe";
	const wchar_t* modName=L"Stronghold.exe";

	DWORD ProcId;


	HANDLE hProcess = 0;
	uintptr_t dynamicPtrBaseAddr;
	uintptr_t moduleBase;
	uintptr_t** Granary_adrr;
	uintptr_t** Armoury_adrr;
	uintptr_t** Stockpile_adrr;

	std::vector<unsigned int> StockPileOffsets = {};
	std::vector<unsigned int> GranaryOffsets = {};
	std::vector<unsigned int> ArmouryOffsets = {};

};

