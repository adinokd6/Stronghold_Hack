#include "cMain.h"
#include <string>
#include <memory>
#include "Enums.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnGranary)
EVT_MENU(10002, cMain::OnStockpile)
EVT_MENU(10003, cMain::OnArmoury)
EVT_BUTTON(10004, cMain::OnHack)
wxEND_EVENT_TABLE()


cMain::cMain()
	: wxFrame(nullptr, wxID_ANY, "Stronghold Fast Hack", wxPoint(30, 30), wxSize(500, 460), (wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)), hackEngine(version)
{
	ChooseVersion();
	CreateWindow();
	InitializeFields();
}

cMain::~cMain()
{

}

void cMain::ChooseVersion()
{
	wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Is it Steam version? If no it will be avaliable only for 1.4.1"), wxT("Version"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

	int ret = dial->ShowModal();
	version = (ret == wxID_YES) ? Version::Steam : Version::NonSteam;
}

void cMain::CreateWindow()
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

	hackButton = new wxButton(this, 10004, "HACK", wxPoint(10, 10), wxSize(465, 50));
	typingFields = new wxTextCtrl * [numberOfFields];
	actualValue = new wxStaticText * [numberOfFields];
}

void cMain::InitializeFields()
{
	std::vector<std::string> fieldValues = GetActualCategoryValues(Category::Granary);

	int column = 0, row = 0;

	for (int i = 0;i < numberOfFields;i++)
	{
		column = i % 2 != 0 ? 1 : 0;
		row += i % 2 != 0 ? 0 : 1;

		if (i >= 9)
		{
			SetFieldValue(column, row, i, fieldValues[i], Category::Stockpile);
			HideField(i);
		}
		else
		{
			SetFieldValue(column, row, i, fieldValues[i], Category::Granary);
		}
	}
}

void cMain::SetFieldValue(int column, int row, int fieldIndex, std::string fieldValue, Category category)
{
	auto imagePath = GetImagePath(fieldIndex, category);
	typingFields[fieldIndex] = new wxTextCtrl(this, wxID_ANY, "", wxPoint(120 + 200 * column, 32 + row * 55), wxSize(50, 20));
	actualValue[fieldIndex] = new wxStaticText(this, wxID_ANY, fieldValue, wxPoint(70 + 200 * column, 32 + row * 55), wxSize(50, 20));
	pictures[fieldIndex] = new wxStaticBitmap(this, wxID_ANY, wxBitmap(imagePath, wxBITMAP_TYPE_PNG), wxPoint(12 + 190 * column, 15 + row * 55), wxSize(48, 48));
}

void cMain::LoadField(Category categoryName, int imageNumber)
{
	std::string imagePath = GetImagePath(imageNumber, categoryName);
	pictures[imageNumber]->SetBitmap(wxBitmap(imagePath, wxBITMAP_TYPE_PNG));

	pictures[imageNumber]->Show();
	typingFields[imageNumber]->Show();
	actualValue[imageNumber]->Show();
}

void cMain::HideField(int number)
{
	pictures[number]->Hide();
	typingFields[number]->Hide();
	actualValue[number]->Hide();
}

void cMain::UpdateLabel(int number, std::string value, Category category)
{
	typingFields[number]->Clear();

	LoadField(category, number);
	actualValue[number]->SetLabel(value);
}

void cMain::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void cMain::OnHack(wxCommandEvent& event)
{
	std::string arr_of_values[12] = {};

	for (int i = 0;i < numberOfFields;i++)
	{
		if ((typingFields[i]->IsEmpty()) == true)
		{
			arr_of_values[i] = "null";
		}
		else
		{
			arr_of_values[i] = typingFields[i]->GetValue();
		}
	}

	hackEngine.hack_value(actualCategory, arr_of_values);
}

void cMain::OnArmoury(wxCommandEvent& event)
{
	std::vector<std::string> fieldValue = GetActualCategoryValues(Category::Armoury);

	for (int i = 0;i < numberOfFields;i++)
	{
		if (i > 7)
		{
			HideField(i);
		}
		else
		{
			UpdateLabel(i, fieldValue[i], Category::Armoury);
		}
	}
}

void cMain::OnStockpile(wxCommandEvent& event)
{
	std::vector<std::string> fieldValue = GetActualCategoryValues(Category::Stockpile);

	for (int i = 0;i < numberOfFields;i++)
	{
		UpdateLabel(i, fieldValue[i], Category::Stockpile);
	}
}

void cMain::OnGranary(wxCommandEvent& event)
{
	std::vector<std::string> fieldValue = GetActualCategoryValues(Category::Granary);

	for (int i = 0;i < numberOfFields;i++)
	{
		if (i > 8)
		{
			HideField(i);
		}
		else
		{
			UpdateLabel(i, fieldValue[i], Category::Granary);
		}
	}
}

std::vector<std::string> cMain::GetActualCategoryValues(Category category)
{
	SetCategory(category);
	return hackEngine.value_return(category);
}

std::string cMain::GetImagePath(int imageNumber, Category category)
{
	std::string imagePath;
	switch (category) {
	case Category::Armoury:
		imagePath += "Armoury\\" + std::to_string(imageNumber + 1) + ".png";
		break;
	case Category::Stockpile:
		imagePath += "Stockpile\\" + std::to_string(imageNumber + 1) + ".png";
		break;
	case Category::Granary:
		imagePath += "Granary\\" + std::to_string(imageNumber + 1) + ".png";
		break;
	}

	return imagePath;
}

void cMain::SetCategory(Category category)
{
	actualCategory = category;
}