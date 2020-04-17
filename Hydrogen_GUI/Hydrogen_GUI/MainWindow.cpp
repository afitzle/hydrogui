#include "MainWindow.h"

MainWindow::MainWindow(wxWindow *parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name) :
	wxFrame(parent, id, title, pos, size, style, name)
{
	wxPanel* panel = new wxPanel(this);
	wxButton* btn = new wxButton(panel, wxID_ANY, "Button", wxPoint(250,100),wxSize(100, 50));

}


MainWindow::~MainWindow()
{
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(TRUE);
}
