#include "cMain.h"
#include <string>


//wxMessageBox();



wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(325, 400), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX))
{

	menuFile = new wxMenu;
	menuBar = new wxMenuBar;


	menuFile->Append(wxID_ANY, wxT("&Granary"));
	menuFile->Append(wxID_ANY, wxT("&Stockpile"));
	menuFile->Append(wxID_ANY, wxT("&Armoury"));
	menuFile->AppendSeparator();

	quit = new wxMenuItem(menuFile, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	menuFile->Append(quit);

	menuBar->Append(menuFile, wxT("&Options"));
	SetMenuBar(menuBar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(cMain::OnExit));
	Centre();

	hack_button = new wxButton(this,10001, "HACK",wxPoint(10,10),wxSize(290,50));
	typing_fields = new wxTextCtrl*[numbers_of_fields];
	actual_value = new wxStaticText*[numbers_of_fields];





	//pictures = new wxImage * [];
	for (int i = 0;i < numbers_of_fields;i++)
	{
		typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120, 70+i*35), wxSize(50, 20));
		actual_value[i] = new wxStaticText(this, wxID_ANY, "1500", wxPoint(70, 70 + i * 35), wxSize(50, 20));
		//pictures[i] = new wxImage();
		//std::string s = std::to_string(i % 2);
		//s.append(".png");
		//pictures[i]->LoadFile(wxT(s), wxBITMAP_TYPE_PNG);
	}
	

}

cMain::~cMain()
{
	delete[]typing_fields;
	delete[]actual_value;
	//delete[]pictures;
}


void cMain::OnButtonClicked(wxCommandEvent& evnt)
{
	
}

void cMain::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void cMain::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Created by adinokd6. For help or advice visit my YouTube chanell or github site. ",
		"Stronghold Fast Hack", wxOK | wxICON_INFORMATION);
}