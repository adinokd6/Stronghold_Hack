#pragma once

#include "wx/wx.h"
#include <string>



class cMain : public wxFrame
{
public: 
	cMain();
	~cMain();
	void OnButtonClicked(wxCommandEvent& evnt);
	wxDECLARE_EVENT_TABLE();
private:
	int numbers_of_fields = 8;
	wxButton *hack_button = nullptr;
	wxTextCtrl **typing_fields;
	wxStaticText **actual_value;
	wxImage **pictures;
};

