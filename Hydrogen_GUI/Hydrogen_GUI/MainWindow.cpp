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
		menuConsole->Append(2, "&Install Hydrogen in Docker..\tCtrl-H",
                     "Redirects to hydrogui git repository");			 
    menuBar->Append(menuFile, "About");
	menuBar->Append(menuConsole, "Console");
    SetMenuBar( menuBar );

	wxPanel* panel = new wxPanel(this);


	 			
    wxTextCtrl *text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10,10), wxSize(140, 30), 0,
					  wxDefaultValidator, wxTextCtrlNameStr);


    wxButton* graphBtn = new wxButton(panel, 4, "Select MVICFG", wxPoint(10,50),wxSize(125, 50));
    Bind(wxEVT_BUTTON, &MainWindow::SelectMVICFG, this, 4);
    wxButton* sourceBtn = new wxButton(panel, 5, "Select Source Files", wxPoint(140,50),wxSize(125, 50));
    Bind(wxEVT_BUTTON, &MainWindow::selectSource, this, 5);
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
	//working example of interacting with docker with our app 
	wxString test = "sudo docker exec Hydrogen_Env git clone https://github.com/iowastateuniversity-programanalysis/hydrogen.git /home/Hydrogen/MVICFG"; 
	wxArrayString out = doExecute(test);
}
/**
 * doExecute
 * 	Executes a command and returns the output generate
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
	size_t outputCount = output.GetCount();
	size_t errorCount = errors.GetCount();
	//no output
	// if (!outputCount) return output;
	
	// std::cout << cmd.c_str() + "\n";
	//prints output (debugging purposes)		
	for ( size_t n = 0; n < outputCount; n++ )
    {
		std::cout<< output[n].c_str() + "\n";
    }
	
	for ( size_t n = 0; n < errorCount; n++ )
    {
        std::cout<< errors[n].c_str() + "\n";
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

void selectSource(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(this, ("Select an MVICFG to view"), wxEmptyString, wxEmptyString,
						"C Files (*.c)|*.c", wxFD_MULTIPLE, wxDefaultPosition);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
      wxArrayString CurrentDocPaths;
      OpenDialog->GetPaths(CurrentDocPaths);
      std::cout << CurrentDocPaths.GetCount();
            // Sets our current document to the file the user selected
            //system("xdot " + CurrentDocPath);
    }

    // Clean up after ourselves
    OpenDialog->Destroy();
    
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
