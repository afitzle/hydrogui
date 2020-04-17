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
    wxMenuBar *menuBar = new wxMenuBar;
			wxMenu *menuFile = new wxMenu;
	    menuFile->Append(1, "&Help...\tCtrl-H",
                     "Redirects to hydrogui git repository");
				menuFile->AppendSeparator();	
    menuBar->Append(menuFile, "About");
    SetMenuBar( menuBar );

	wxPanel* panel = new wxPanel(this);


	 			
    wxTextCtrl *text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10,10), wxSize(140, 30), 0,
					  wxDefaultValidator, wxTextCtrlNameStr);
	wxButton* btn = new wxButton(panel, wxID_ANY, "Button", wxPoint(250,100),wxSize(100, 50));
	
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, 1);
}


MainWindow::~MainWindow()
{
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(TRUE);
}


void MainWindow::OnAbout(wxCommandEvent& event)
{
    static wxString s_url(wxT("https://github.com/afitzle/hydrogui"));
    if ( !wxLaunchDefaultBrowser(s_url) )
    {
        wxLogError(wxT("Failed to open URL \"%s\""), s_url.c_str());
    }
}
