#include "App.h"
#include "id.h"
#include "MainWindow.h"
#include <wx/textctrl.h>
IMPLEMENT_APP(App); //main

App::App()
{
}
bool App::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}
	MainWindow *main = new MainWindow(nullptr,
		window::id::MAINWINDOW,
		_("hydrogui"),
		wxPoint(100,50),
		wxSize(375,350));
	main->checkDockerInit();
	main->Show();
	SetTopWindow(main);
	return true;
}

App::~App()
{
}
