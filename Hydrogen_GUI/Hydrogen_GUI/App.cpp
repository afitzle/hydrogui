#include "App.h"
#include "id.h"
#include "MainWindow.h"
#include<wx/textctrl.h>
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
		_("Main Window"));
	main->Show();
	SetTopWindow(main);
	return true;
}

App::~App()
{
}
