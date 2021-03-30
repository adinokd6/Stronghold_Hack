#include "cMain.h"
#include <string>


#define Stockpile 0
#define Granary 3 //because its 3 less items in granary and kitchen
#define Armoury 4 //same case as up



wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnGranary)
EVT_MENU(10002,cMain::OnStockpile)
EVT_MENU(10003,cMain::OnArmoury)
EVT_BUTTON(10004,cMain::OnHack)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(500, 700), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX))
{

	menuFile = new wxMenu;
	menuBar = new wxMenuBar;

	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	menuFile->Append(10001, wxT("&Granary and Kitchen"));
	menuFile->Append(10002, wxT("&Stockpile"));
	menuFile->Append(10003, wxT("&Armoury"));
	menuFile->AppendSeparator();

	quit = new wxMenuItem(menuFile, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	menuFile->Append(quit);

	menuBar->Append(menuFile, wxT("&Options"));
	SetMenuBar(menuBar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(cMain::OnExit));
	Centre();

	hack_button = new wxButton(this,10004, "HACK",wxPoint(10,10),wxSize(295,50));
	typing_fields = new wxTextCtrl*[numbers_of_fields];
	actual_value = new wxStaticText*[numbers_of_fields];

	std::string tmp_string;

	std::vector<int> tmp_values=hack_Engine.value_return(Granary);

	actual_category = Granary;

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if(i>=9)
		{
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120+250*(i%2), 87 + (i%5) * 54), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70+200*(i%2), 87 + (i % 5) * 54), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Stockpile\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12+190*i%2, 70 + (i % 5) * 54), wxSize(48, 48));

			pictures[i]->Hide();
			typing_fields[i]->Hide();
			actual_value[i]->Hide();
		}
		else
		{
			tmp_string = std::to_string(tmp_values[i]);
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120+250*(i%2), 87 + (i % 5) * 54), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70+200 * (i % 2), 87 + (i % 5) * 54), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Granary\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12+190 * (i % 2), 70 + (i % 5) * 54), wxSize(48, 48));

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
	std::string arr_of_values[12] = {};

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

		pictures[number]->Show();
		typing_fields[number]->Show();
		actual_value[number]->Show();
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
		
		s = std::to_string(tmp_values[i]);
		Load_Images("Stockpile", i);
		actual_value[i]->SetLabel(s);
		
	}
}

void cMain::OnGranary(wxCommandEvent& event)
{
	actual_category = Granary;

	std::string s;
	std::vector<int> tmp_values = hack_Engine.value_return(Granary);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if (i>9)
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


