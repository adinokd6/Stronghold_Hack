#pragma once

#include "wx/wx.h"

#include <string>
#include "cEngine.h"

#define Armoury 0
#define Granary 1
#define Stockpile 3




class cMain : public wxFrame
{
public: 
	cMain();
	~cMain();
	void OnExit(wxCommandEvent& event);
	void Create_Window();
	void Initialize_Fields();

	void OnArmoury(wxCommandEvent& event);
	void OnStockpile(wxCommandEvent& event);
	void OnGranary(wxCommandEvent& event);
	void OnHack(wxCommandEvent& event);

	void Load_Field(std::string name,int number);
	void Hide_Field(int number);
	void Update_Label(int number, int value, std::string category);

	void Choose_version();


	wxDECLARE_EVENT_TABLE();
private:
	int numbers_of_fields = 12;
	int current_value;
	int actual_category;
	int version; //it can be 1.4.1 or steam 1.5

	cEngine hack_Engine;

	wxButton *hack_button = nullptr;
	wxTextCtrl **typing_fields;
	wxStaticText **actual_value;
	wxMenu *menuFile;
	wxMenuBar* menuBar;
	wxMenuItem* quit;
	wxStaticBitmap**pictures= new wxStaticBitmap * [numbers_of_fields];;
	
};

