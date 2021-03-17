#include "cMain.h"
#include <string>


//wxMessageBox();



wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnGranary)
EVT_MENU(10002,cMain::OnStockpile)
EVT_MENU(10003,cMain::OnArmoury)
EVT_MENU(10004,cMain::OnHack)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(325, 520), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX))
{

	menuFile = new wxMenu;
	menuBar = new wxMenuBar;

	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	menuFile->Append(10001, wxT("&Granary"));
	menuFile->Append(10002, wxT("&Stockpile"));
	menuFile->Append(10003, wxT("&Armoury"));
	menuFile->AppendSeparator();

	quit = new wxMenuItem(menuFile, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	menuFile->Append(quit);

	menuBar->Append(menuFile, wxT("&Options"));
	SetMenuBar(menuBar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(cMain::OnExit));
	Centre();

	hack_button = new wxButton(this,10004, "HACK",wxPoint(10,10),wxSize(290,50));
	typing_fields = new wxTextCtrl*[numbers_of_fields];
	actual_value = new wxStaticText*[numbers_of_fields];

	std::string s;

	for (int i = 0;i < numbers_of_fields;i++)
	{
		s.append("Granary");
		s.append("\\");
		s.append(std::to_string(i + 1));
		s.append(".png");

		typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120, 87+i*54), wxSize(50, 20));
		actual_value[i] = new wxStaticText(this, wxID_ANY, "1500", wxPoint(70, 87 + i * 54), wxSize(50, 20));

		pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap(s, wxBITMAP_TYPE_PNG), wxPoint(12, 70 + i * 54), wxSize(48, 48));
		pictures[i]->Refresh();
		s.clear();

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

void cMain::OnHack(wxCommandEvent& event)
{

}

void cMain::Load_Images(std::string name,int number)
{
		pictures[number]->SetBitmap(wxBitmap(name+"\\"+ std::to_string(number + 1)+".png", wxBITMAP_TYPE_PNG));
		if (name == "Armoury" || name == "Granary")
		{
			pictures[number]->Show();
			typing_fields[number]->Show();
			actual_value[number]->Show();
		}
}

void cMain::OnArmoury(wxCommandEvent& event)
{
	std::string s;
	for (int i = 0;i < numbers_of_fields;i++)
	{
		
		s=std::to_string(i * 30);
		actual_value[i]->SetLabel(s);

		Load_Images("Armoury", i);

	}

}

void cMain::OnStockpile(wxCommandEvent& event)
{
	for (int i = 0;i < numbers_of_fields;i++)
	{
		std::string s;
		s = std::to_string(i * 22);
		
		typing_fields[i]->Clear();
		actual_value[i]->SetLabel(s);
		if (i < 5)
		{
			Load_Images("Stockpile", i);
		}
		else
		{
			typing_fields[i]->Hide();
			actual_value[i]->Hide();
			pictures[i]->Hide();
		}
		
	}
}

void cMain::OnGranary(wxCommandEvent& event)
{
	std::string s;

	for (int i = 0;i < numbers_of_fields;i++)
	{
		
		s = std::to_string(i *45);

		typing_fields[i]->Clear();
		actual_value[i]->SetLabel(s);

		Load_Images("Granary", i);
	}
}


