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


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(500, 460), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)), hack_Engine(version)
{
	Choose_version();

	Create_Window();

	Initialize_Fields();

}

cMain::~cMain()
{
	delete[]typing_fields;
	delete[]actual_value;
	delete[]pictures;
}

void cMain::Choose_version()
{
	wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Is it Steam version? If no it will be avaliable only for 1.4.1"), wxT("Version"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

	int ret = dial->ShowModal();
	dial->Destroy();

	if (ret == wxID_YES)
	{
		version = 1;
	}
	else
	{
		version = 2;
	}

}

void cMain::Create_Window()
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

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMain::OnExit));
	Centre();

	hack_button = new wxButton(this, 10004, "HACK", wxPoint(10, 10), wxSize(465, 50));
	typing_fields = new wxTextCtrl * [numbers_of_fields];
	actual_value = new wxStaticText * [numbers_of_fields];
}

void cMain::Initialize_Fields()
{
	actual_category = Granary;

	std::string tmp_string;

	std::vector<int> tmp_values = hack_Engine.value_return(Granary);

	int column = 0, row = 0;

	for (int i = 0;i < numbers_of_fields;i++)
	{

		if (i % 2 != 0)
		{
			column = 1;
		}
		else
		{
			row += 1;
			column = 0;
		}

		if (i >= 9)
		{
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120 + 200 * column, 32 + row * 55), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70 + 200 * column, 32 + row * 55), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Stockpile\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12 + 190 * column, 15 + row * 55), wxSize(48, 48));

			Hide_Field(i);
		}
		else
		{
			tmp_string = std::to_string(tmp_values[i]);
			typing_fields[i] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120 + 200 * column, 32 + row * 55), wxSize(50, 20));
			actual_value[i] = new wxStaticText(this, wxID_ANY, tmp_string, wxPoint(70 + 200 * column, 32 + row * 55), wxSize(50, 20));
			pictures[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Granary\\" + std::to_string(i + 1) + ".png", wxBITMAP_TYPE_PNG), wxPoint(12 + 190 * column, 15 + row * 55), wxSize(48, 48));

		}

	}
}

void cMain::Load_Field(std::string name, int number)
{
	pictures[number]->SetBitmap(wxBitmap(name + "\\" + std::to_string(number + 1) + ".png", wxBITMAP_TYPE_PNG));

	pictures[number]->Show();
	typing_fields[number]->Show();
	actual_value[number]->Show();
}

void cMain::Hide_Field(int number)
{
	pictures[number]->Hide();
	typing_fields[number]->Hide();
	actual_value[number]->Hide();
}

void cMain::Update_Label(int number,int value,std::string category)
{
	typing_fields[number]->Clear();

	std::string tmp_string = std::to_string(value);

	Load_Field(category, number);
	actual_value[number]->SetLabel(tmp_string);
}

void cMain::OnExit(wxCommandEvent& event)
{
	Close(true);
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

void cMain::OnArmoury(wxCommandEvent& event)
{
	actual_category = Armoury;

	std::vector<int> tmp_values = hack_Engine.value_return(Armoury);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if (i > 7)
		{
			Hide_Field(i);
		}
		else
		{
			Update_Label(i, tmp_values[i], "Armoury");
		}

	}

}

void cMain::OnStockpile(wxCommandEvent& event)
{
	actual_category = Stockpile;

	std::vector<int> tmp_values = hack_Engine.value_return(Stockpile);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		Update_Label(i, tmp_values[i], "Stockpile");
	}
}

void cMain::OnGranary(wxCommandEvent& event)
{
	actual_category = Granary;

	std::vector<int> tmp_values = hack_Engine.value_return(Granary);

	for (int i = 0;i < numbers_of_fields;i++)
	{
		if (i>8)
		{
			Hide_Field(i);
		}
		else
		{
			Update_Label(i, tmp_values[i], "Granary");
		}

	}
}


