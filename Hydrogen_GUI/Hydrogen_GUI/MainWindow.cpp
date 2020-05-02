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


void MainWindow::generateGraph()
{
	//buildninja dir /home/Hydrogen/MVICFG/BuildNinja

	//cd TestPrograms/Buggy
	wxString prog1;
	wxString prog2;
	wxString pathToHydro="/home/Hydrogen/MVICFG/BuildNinja/Hydrogen.out ";
	wxString execScript="sudo docker exec Hydrogen_Env chmod 777 /home/Hydrogen/MVICFG/hydro-clang.sh";
	wxString pathToScript="sudo docker exec Hydrogen_Env bash ./home/Hydrogen/MVICFG/hydro-clang.sh";
	wxString pathToProg1=" /home/Hydrogen/MVICFG/TestPrograms/Buggy/";
	wxString pathToProg2=" /home/Hydrogen/MVICFG/TestPrograms/Correct/";
	wxString dropScript = "docker cp hydro-clang.sh Hydrogen_Env:/home/Hydrogen/MVICFG/hydro-clang.sh";
	wxString pickupDot = "docker cp Hydrogen_Env:home/Hydrogen/MVICFG/BuildNinja/MVICFG.dot mydot.dot";
	
	///home/Hydrogen/MVICFG/TestPrograms/Buggy
	
	//sudo docke exec Hydrogen_Env 
	// wxString comp1 ="sudo docker exec clang -c -O0 -Xclang -disable-O0-optnone -g -emit-llvm -S /home/Hydrogen/MVICFG/TestPrograms/Buggy/Prog.c -o /home/Hydrogen/MVICFG/TestPrograms/Buggy/ProgV1.bc";
	// wxArrayString out1 = doExecute(comp1);
	// ///home/Hydrogen/MVICFG/TestPrograms/Correct
	//wxString comp2 = "sudo docker exec Hydrogen_Env clang -c -O0 -Xclang -disable-O0-optnone -g -emit-llvm -S /home/Hydrogen/MVICFG/TestPrograms/Correct/Prog.c -o /home/Hydrogen/MVICFG/TestPrograms/Correct/ProgV2.bc";
	// wxArrayString out2 = doExecute(com
	// wxString del1 = "sudo docker exec Hydrogen_Env rm " + pathToProg2 +"ProgV2.bc";

	// + pathToProg2 + "ProgV2.bc :: "+ pathToProg1 +"Prog.c :: "+pathToProg2+"Prog.c";
	wxArrayString dumpScript = doExecute(dropScript);
	std::cout<<"\n" + pathToScript + "\n";
	// wxString tryit = pathToHydro +" "+ pathToProg1 + "ProgV1.bc " + pathToProg2 + "ProgV2.bc "+ "::"  + pathToProg1 +" :: "+pathToProg2 + "Prog.c";
	wxArrayString hydroOut=doExecute(pathToScript);

	wxArrayString snagDot=doExecute(pickupDot);
	// wxArrayString snagDot = doExecute();
	// wxArrayString oot = doExecute(tryit);
	// doExecute(del);
	// doExecute(del1)++++++++
}

/**
 * OnExec 
 * 	Utilizes doExecute to to execute a sample command.
 *  Output is printed to the commandline.
 * @param  {wxCommandEvent} event : 
 */
void MainWindow::OnExec(wxCommandEvent& event)
{
	generateGraph();
	//working example of interacting with docker with our app 
	// wxString test = "sudo docker exec Hydrogen_Env git clone https://github.com/iowastateuniversity-programanalysis/hydrogen.git /home/Hydrogen/MVICFG"; 
	// wxArrayString out = doExecute(test);
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
