#pragma once

#include "wx/wx.h"

#include <string>



class cMain : public wxFrame
{
public: 
	cMain();
	~cMain();
	void OnButtonClicked(wxCommandEvent& evnt);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnArmoury(wxCommandEvent& event);
	void OnStockpile(wxCommandEvent& event);
	void OnGranary(wxCommandEvent& event);
	void OnHack(wxCommandEvent& event);

	void Load_Images(std::string name,int number);


	wxDECLARE_EVENT_TABLE();
private:
	int numbers_of_fields = 7;
	wxButton *hack_button = nullptr;
	wxTextCtrl **typing_fields;
	wxStaticText **actual_value;
	wxMenu *menuFile;
	wxMenuBar* menuBar;
	wxMenuItem* quit;
	wxStaticBitmap**pictures= new wxStaticBitmap * [numbers_of_fields];;
	
};

