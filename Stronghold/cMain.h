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

	void Create_Bar();
	void Create_Menu();
	


	wxDECLARE_EVENT_TABLE();
private:
	int numbers_of_fields = 8;
	wxButton *hack_button = nullptr;
	wxTextCtrl **typing_fields;
	wxStaticText **actual_value;
	wxMenu *menuFile;
	wxMenuBar* menuBar;
	wxMenuItem* quit;
	wxImage **pictures;
};

