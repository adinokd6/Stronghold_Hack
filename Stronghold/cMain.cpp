#include "cMain.h"
#include <string>

#define Armoury 0
#define Granary 1
#define Stockpile 3

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnGranary)
EVT_MENU(10002,cMain::OnStockpile)
EVT_MENU(10003,cMain::OnArmoury)
EVT_BUTTON(10004,cMain::OnHack)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(325, 570), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX))
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

	std::string tmp_string;

	std::vector<int> tmp_values=hack_Engine.value_return(Granary);

	actual_category = Granary;

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if (i == 7)
		{
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120, 87 + i * 54), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70, 87 + i * 54), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Armoury\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12, 70 + i * 54), wxSize(48, 48));

			pictures[i]->Hide();
			typing_fields[i]->Hide();
			actual_value[i]->Hide();
		}
		else
		{
			tmp_string = std::to_string(tmp_values[i]);
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120, 87 + i * 54), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70, 87 + i * 54), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Granary\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12, 70 + i * 54), wxSize(48, 48));

		}

	}
	

}

cMain::~cMain()
{
	delete[]typing_fields;
	delete[]actual_value;
	delete[]pictures;
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
	std::string arr_of_values[8] = {};

	for(int i = 0;i < numbers_of_fields;i++)
	{
		if ( (typing_fields[i]->IsEmpty()) == true)
		{
			arr_of_values[i] = "null";
		}
		else
		{
			arr_of_values[i] = typing_fields[i]->GetValue();
		}
	}

	hack_Engine.hack_value(actual_category, arr_of_values);

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
	actual_category = Armoury;
	std::string s;

	std::vector<int> tmp_values = hack_Engine.value_return(Armoury);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		s=std::to_string(tmp_values[i]);

		actual_value[i]->SetLabel(s);

		Load_Images("Armoury", i);

	}

}

void cMain::OnStockpile(wxCommandEvent& event)
{
	actual_category = Stockpile;
	std::string s;

	std::vector<int> tmp_values = hack_Engine.value_return(Stockpile);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		typing_fields[i]->Clear();
		
		if (i < 5)
		{
			s = std::to_string(tmp_values[i]);
			Load_Images("Stockpile", i);
			actual_value[i]->SetLabel(s);
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
	actual_category = Granary;

	std::string s;
	std::vector<int> tmp_values = hack_Engine.value_return(Granary);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if (i == 7)
		{
			typing_fields[i]->Hide();
			actual_value[i]->Hide();
			pictures[i]->Hide();
		}
		else
		{
			s = std::to_string(tmp_values[i]);

			typing_fields[i]->Clear();
			actual_value[i]->SetLabel(s);

			Load_Images("Granary", i);
		}

	}
}


