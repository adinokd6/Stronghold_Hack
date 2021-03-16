#include "App.h"

wxIMPLEMENT_APP(App);


App::App()
{



}

App::~App()
{


}

bool App::OnInit()
{
	m_frame_1 = new cMain();
	m_frame_1->Show();

	return true;
}

