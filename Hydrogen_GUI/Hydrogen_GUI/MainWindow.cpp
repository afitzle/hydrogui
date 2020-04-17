#include "MainWindow.h"
#include <iostream>


MainWindow::MainWindow(wxWindow *parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name) :
	wxFrame(parent, id, title, pos, size, style, name)
{
  	wxPanel *frame = new wxPanel(this);
	frame->Show();
        wxTextCtrl *text = new wxTextCtrl(frame, wxID_ANY, "", wxPoint(10,10), wxSize(140, 30), 0,
					  wxDefaultValidator, wxTextCtrlNameStr);
}


MainWindow::~MainWindow()
{
}
