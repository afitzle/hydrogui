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
			wxMenu *menuConsole = new wxMenu;
	    menuFile->Append(1, "&Help...\tCtrl-H",
                     "Redirects to hydrogui git repository");
		menuConsole->Append(2, "&Console..\tCtrl-H",
                     "Redirects to hydrogui git repository");			 
    menuBar->Append(menuFile, "About");
	menuBar->Append(menuConsole, "Console");
    SetMenuBar( menuBar );

	wxPanel* panel = new wxPanel(this);


	 			
    wxTextCtrl *text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10,10), wxSize(140, 30), 0,
					  wxDefaultValidator, wxTextCtrlNameStr);


    wxButton* graphBtn = new wxButton(panel, 4, "Select MVICFG", wxPoint(10,50),wxSize(125, 50));
    Bind(wxEVT_BUTTON, &MainWindow::SelectMVICFG, this, 4);
	wxButton* btn = new wxButton(panel, wxID_ANY, "Button", wxPoint(250,100),wxSize(100, 50));
	
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, 1);
	Bind(wxEVT_MENU, &MainWindow::OnExec, this, 2);
}


MainWindow::~MainWindow()
{
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(TRUE);
}



/**
 * OnExec 
 * 	Utilizes doExecute to to execute a sample command.
 *  Output is printed to the commandline.
 * @param  {wxCommandEvent} event : 
 */
void MainWindow::OnExec(wxCommandEvent& event)
{
	wxString test = "ps -a";
	wxArrayString out = doExecute(test);
}
/**
 * doExecute
 * 	Executes a command and returns the output generated
 *	by the program being executed.
 * @param  {wxString} cmd   : command to be executed
 * @return {wxArrayString} output  : Array 
 * 			(each element represents a line) of output returned from the command
 * 			specified by cmd.
 */
wxArrayString MainWindow::doExecute(wxString& cmd)
{
	wxArrayString output, errors;
	int code = wxExecute(cmd, output, errors);
	size_t count = output.GetCount();
	//no output
	if (!count) return output;

	//prints output (debugging purposes)		
	for ( size_t n = 0; n < count; n++ )
    {
        std::cout<< output[n].c_str() + "\n";
    }
	return output;
}


void MainWindow::OnAbout(wxCommandEvent& event)
{
    static wxString s_url(wxT("https://github.com/afitzle/hydrogui"));
    if ( !wxLaunchDefaultBrowser(s_url) )
    {
        wxLogError(wxT("Failed to open URL \"%s\""), s_url.c_str());
    }
}

void MainWindow::SelectMVICFG(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, ("Select an MVICFG to view"), wxEmptyString, wxEmptyString, "Dot Files (*.dot)|*.dot"
		, wxFD_OPEN, wxDefaultPosition);
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		wxString CurrentDocPath = OpenDialog->GetPath();
		// Sets our current document to the file the user selected
		system("xdot " + CurrentDocPath);
	}

	// Clean up after ourselves
	OpenDialog->Destroy();
}
