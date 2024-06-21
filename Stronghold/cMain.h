#pragma once

#include "wx/wx.h"

#include <string>
#include "cEngine.h"
#include "Enums.h";




class cMain : public wxFrame
{
public: 
	cMain();
	~cMain();

	wxDECLARE_EVENT_TABLE();
private:
	int numberOfFields = 12;
	int currentValue;
	int actualCategory;
	int version; //it can be 1.4.1 or steam 1.5

	cEngine hackEngine;

	wxButton *hackButton = nullptr;
	wxTextCtrl** typingFields;
	wxStaticText** actualValue;
	wxStaticBitmap** pictures = new wxStaticBitmap * [numberOfFields];;
	wxMenu *menuFile;
	wxMenuBar* menuBar;
	wxMenuItem* quit;
	void SetCategory(Category category);
	void OnExit(wxCommandEvent& event);
	void CreateWindow();
	void InitializeFields();

	void OnArmoury(wxCommandEvent& event);
	void OnStockpile(wxCommandEvent& event);
	void OnGranary(wxCommandEvent& event);
	void OnHack(wxCommandEvent& event);

	void LoadField(Category category, int number);
	void HideField(int number);
	void UpdateLabel(int number, std::string value, Category category);
	void SetFieldValue(int column, int row, int fieldIndex, std::string fieldValue, Category category);
	std::string GetImagePath(int imageNumber, Category category);

	void ChooseVersion();
	std::vector<std::string> GetActualCategoryValues(Category category);
	
};

