#pragma once


#include "wx/wx.h"
#include "cMain.h"

class App : public wxApp
{

public:
	App();
	~App();
	virtual bool OnInit();
private:
	cMain* m_frame_1 = nullptr;
};

