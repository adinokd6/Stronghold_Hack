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
	void OnAbout(wxCommandEvent& event);

	void OnArmoury(wxCommandEvent& event);
	void OnStockpile(wxCommandEvent& event);
	void OnGranary(wxCommandEvent& event);
	void OnHack(wxCommandEvent& event);

	void Load_Images(std::string name,int number);


	wxDECLARE_EVENT_TABLE();
private:
	cEngine hack_Engine;
	int numbers_of_fields = 8;
	int current_value;
	int actual_category;
	wxButton *hack_button = nullptr;
	wxTextCtrl **typing_fields;
	wxStaticText **actual_value;
	wxMenu *menuFile;
	wxMenuBar* menuBar;
	wxMenuItem* quit;
	wxStaticBitmap**pictures= new wxStaticBitmap * [numbers_of_fields];;
	
};

