#include <iostream>
#include <fstream>
#include <regex>
#include <wx/popupwin.h>
#include "MainWindow.h"

//Coords for right and left side of window
#define RIGHT 200
#define LEFT 10
//Flags harvest buggy/fixed files
#define BUGGY 0
#define FIXED 1

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
	wxMenu *menuCleanFiles = new wxMenu;
		menuFile->Append(9, "&Open .dot file...\tCtrl-D",
	"Open a .dot file from local filesystem");
	menuFile->Append(1, "&About...\tCtrl-H",
					"Redirects to hydrogui git repository");

	menuConsole->Append(2, "&Run Hydrogen..\tCtrl-H",
					"Run Hydrogen and transfer dotfile");

	menuConsole->Append(8,"&Clean Remote Files..\tCtrl-G",
					"Delete remote files");						 
	
	menuBar->Append(menuFile, "File");
	menuBar->Append(menuConsole, "Execute");
    SetMenuBar( menuBar );

	wxPanel* panel = new wxPanel(this);

    wxButton* buggyBtn = new wxButton(panel, 5, "Select Buggy Files", wxPoint(LEFT,10),wxSize(150, 50));
    wxButton* fixedBtn = new wxButton(panel, 6, "Select Fixed Files", wxPoint(RIGHT,10),wxSize(150, 50));

	log = new wxTextCtrl(panel, wxID_OK,"", wxPoint(LEFT,75), wxSize(340,200),wxTE_MULTILINE|wxTE_READONLY);

	
	//init buttons/triggers
	Bind(wxEVT_BUTTON, &MainWindow::selectSource, this, 5);
	Bind(wxEVT_BUTTON, &MainWindow::selectFixed, this, 6);
	Bind(wxEVT_MENU, &MainWindow::SelectMVICFG, this, 9);
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, 1);
	Bind(wxEVT_MENU, &MainWindow::OnExec, this, 2);
	Bind(wxEVT_MENU,&MainWindow::OnClean, this, 8);
}


MainWindow::~MainWindow()
{
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(TRUE);
}

/**
 * checkDockerInit 
 * Starts Hydrogen_Env if the container is stopped
 * when the hydrogui program runs.
 */
void MainWindow::checkDockerInit()
{
	wxString check = "docker start Hydrogen_Env";
	wxArrayString res = doExecute(check);
}


void MainWindow::generateGraph()
{

	wxString prog1;
	wxString prog2;
	wxString pathToHydro="/home/Hydrogen/MVICFG/BuildNinja/Hydrogen.out ";
	wxString execScript="sudo docker exec Hydrogen_Env chmod 777 /home/Hydrogen/MVICFG/hydro-clang.sh";
	wxString pathToScript="sudo docker exec Hydrogen_Env bash ./home/Hydrogen/MVICFG/hydro-clang.sh";
	wxString pathToProg1=" /home/Hydrogen/MVICFG/TestPrograms/Buggy/";
	wxString pathToProg2=" /home/Hydrogen/MVICFG/TestPrograms/Correct/";
	wxString dropScript = "docker cp hydro-clang.sh Hydrogen_Env:/home/Hydrogen/MVICFG/hydro-clang.sh";
	

	wxArrayString dumpScript = doExecute(dropScript);
	std::cout<<"\n" + pathToScript + "\n";
	int i = 0;

	//generates popup and exits function if the user hasn't added any files	
	if(buggyFileNames.GetCount() < 1 || fixedFileNames.GetCount() < 1)
	{
		wxPopupWindow *m_simplePopup;
		m_simplePopup = new wxPopupWindow(this, false );
    	wxPoint pos = ClientToScreen( wxPoint(0,0) );
    	wxSize sz = wxSize(50,50);
    	m_simplePopup->Position( pos, sz );
    	wxLogMessage( "No files found on Hydrogen's container!", m_simplePopup);
   	 	m_simplePopup->Show();
		return;	
	}
	else
	{
		/* code */
	
	wxString pickupDot = "docker cp Hydrogen_Env:home/Hydrogen/MVICFG/BuildNinja/MVICFG.dot v1"+buggyFileNames.Item(0)+"-v2"+fixedFileNames.Item(0)+".dot";
	wxArrayString hydroOut=doExecute(pathToScript);

	wxArrayString snagDot=doExecute(pickupDot);
	}
}

/**
 * OnExec 
 * 	Utilizes doExecute to to execute a sample command.
 *  Output is printed to the commandline.
 * @param  {wxCommandEvent} event : 
 */
void MainWindow::OnExec(wxCommandEvent& event)
{
	//ok
	generateGraph();
	if(buggyFileNames.GetCount() > 0 && fixedFileNames.size() > 0)
	{
	wxString s = "v1"+buggyFileNames.Item(0)+"-v2"+fixedFileNames.Item(0)+".dot";
	parse_dot_file(s.ToStdString());
	}
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

/**
 * OnClean 
 * Checks for on hydrogen image and deletes them.
 * @param  {wxCommandEvent} (event : 
 */
void MainWindow::OnClean(wxCommandEvent& (event))
{

	unsigned int i, j;
	wxString lsCmdBuggy = "sudo docker exec Hydrogen_Env ls /home/Hydrogen/MVICFG/TestPrograms/Buggy/";
	wxString lsCmdCorrect = "sudo docker exec Hydrogen_Env ls /home/Hydrogen/MVICFG/TestPrograms/Correct/";
	wxString cleanBuggy = "sudo docker exec Hydrogen_Env rm  /home/Hydrogen/MVICFG/TestPrograms/Buggy/";
	wxString cleanCorrect = "sudo docker exec Hydrogen_Env rm /home/Hydrogen/MVICFG/TestPrograms/Correct/";
	
	wxArrayString deletedBuggy;
	wxArrayString deletedCorrect;
	
	// buggyFileCmd = "sudo docker rm Hydrogen_Env:/home/Hydrogen/MVICFG/TestPrograms/Buggy/"+buggyFileNames.Item(i);
	std::cout<<"---Found buggy 	files---"<<std::endl;
	deletedBuggy = doExecute(lsCmdBuggy);
	std::cout<<"---Found correct files---"<<std::endl;
	deletedCorrect = doExecute(lsCmdCorrect);

	for(i =0; i < deletedBuggy.GetCount(); i++)
	{
		doExecute(cleanBuggy.Clone().append(deletedBuggy.Item(i)));
	}
	for(j =0; j < deletedCorrect.GetCount(); j++)
	{
		doExecute(cleanCorrect.Clone().append(deletedCorrect.Item(j)));
	}
	std::cout<<"------Cleaned-------"<<std::endl;
	buggyFileNames.clear();
	buggyFilesAbsolute.clear();
	fixedFileNames.clear();
	fixedFilesAbsolute.clear();


}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    static wxString s_url(wxT("https://github.com/afitzle/hydrogui"));
    if ( !wxLaunchDefaultBrowser(s_url) )
    {
        wxLogError(wxT("Failed to open URL \"%s\""), s_url.c_str());
    }
	
}

/**
 * selectSource 
 * Obtain buggy files from dialogue
 * @param  {wxCommandEvent} WXUNUSED(event) : 
 */
void MainWindow::selectSource(wxCommandEvent& WXUNUSED(event))
{
	selectFiles(BUGGY);    
}

/**
 * selectFixed
 * Obtain buggy files from dialogue
 * @param  {wxCommandEvent} WXUNUSED(event) : 
 */
void MainWindow::selectFixed (wxCommandEvent& WXUNUSED(event))
{
	selectFiles(FIXED);
	ListBuggyAndFixedFiles();    
	TransferBuggyAndFixedFiles();
}

/**
 * selectFiles
 * Handles buggy and fixed file info.
 * Obtains an absolute path and file name for all files and
 * stores them in
 *  wxArrayString buggyFilesAbsolute (absolute)
 *  wxArrayString fixedFilesAbsolute (absolute)
 * 	wxArrayString fixedFileNames (filename)
 *  wxArrayString buggyFileNames (filename)
 * Respectively.
 * @param  {int} MODE : BUGGY or FIXED files to be handled
 */
void MainWindow::selectFiles(int MODE)
{
	//mode is either BUGGY or FIXED
	if(MODE == BUGGY)
	{
			wxFileDialog* OpenDialog = new wxFileDialog(this, ("Select the Source Files to View"), wxEmptyString, wxEmptyString,
							"C Files (*.c)|*.c", wxFD_MULTIPLE, wxDefaultPosition);
		if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
		{
		OpenDialog->GetPaths(buggyFilesAbsolute);
		OpenDialog->GetFilenames(buggyFileNames);
		int count = buggyFilesAbsolute.GetCount();
		int i;
		for(i=0; i<count; i++){
		  std::cout << "Added Buggy File(s): " << buggyFilesAbsolute.Item(i) << std::endl;
			}
				
		OpenDialog->Destroy();		
		}
		
		}

	if(MODE == FIXED)
	{

			wxFileDialog* OpenDialog = new wxFileDialog(this, ("Select the Source Files to View"), wxEmptyString, wxEmptyString,
							"C Files (*.c)|*.c", wxFD_MULTIPLE, wxDefaultPosition);
		if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
		{
		wxArrayString CurrentDocPaths;
		OpenDialog->GetPaths(CurrentDocPaths);
		OpenDialog->GetPaths(fixedFilesAbsolute);
		OpenDialog->GetFilenames(fixedFileNames);
		int count = CurrentDocPaths.GetCount();
		int i;
		for(i=0; i<count; i++){
			std::cout << "Added Fixed File(s): " <<CurrentDocPaths.Item(i) << std::endl;
			
		}
				
		OpenDialog->Destroy();
	}
	
	}


	
}


/**
 * TransferBuggyAndFixedFiles 
 * Puts files in their respective places on the hydrogen docker
 * container
 */
void MainWindow::TransferBuggyAndFixedFiles()
{
	int countFixed = this->fixedFilesAbsolute.GetCount();
	wxString fixedFileCmd;
	
	int countBuggy = this->buggyFilesAbsolute.GetCount();
	wxString buggyFileCmd;

	int i = 0;
	std::cout << "---Transfering buggy and fixed files---" << std::endl;
	for(i=0; i<countBuggy; i++){
			// std::cout << "buggy["<<i<<"]:" << buggyFiles.Item(i) << std::endl;
			buggyFileCmd = "sudo docker cp "+ buggyFilesAbsolute.Item(i) + " Hydrogen_Env:/home/Hydrogen/MVICFG/TestPrograms/Buggy/"+buggyFileNames.Item(i);
			std::cout << "buggy["<<i<<"]:" << buggyFileCmd.c_str() << std::endl;
			doExecute(buggyFileCmd);
	}

	for(i=0; i < countFixed ; i++){
			fixedFileCmd = "sudo docker cp "+ fixedFilesAbsolute.Item(i) + " Hydrogen_Env:/home/Hydrogen/MVICFG/TestPrograms/Correct/"+fixedFileNames.Item(i);
			std::cout << "fixed["<<i<<"]:" << fixedFileCmd.c_str() << std::endl;
			doExecute(fixedFileCmd);
	}
	std::cout << "---		Transferring Done		---" << std::endl;
}


/**
 * ListBuggyAndFixedFiles
 * Prints filepaths of currently stored files obtained
 * through the file selector.
 */
void MainWindow::ListBuggyAndFixedFiles()
{
	int countFixed = this->fixedFilesAbsolute.GetCount();
	int countBuggy = this->buggyFilesAbsolute.GetCount();
	int i = 0;
	std::cout << "---Listing buggy and fixed files---" << std::endl;
	for(i=0; i<countBuggy; i++){
			std::cout << "buggy["<<i<<"]:" << buggyFilesAbsolute.Item(i) << std::endl;
	}

	for(i=0; i < countBuggy ; i++){
			std::cout << "fixed["<<i<<"]:" << fixedFilesAbsolute.Item(i) << std::endl;
	}

	std::cout << "---End buggy and fixed files	---" << std::endl;
}

void MainWindow::SelectMVICFG(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, ("Select an MVICFG to view"), wxEmptyString, wxEmptyString, "Dot Files (*.dot)|*.dot"
		, wxFD_OPEN, wxDefaultPosition);
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		wxString CurrentDocPath = OpenDialog->GetPath();
		system("xdot " + CurrentDocPath);
		clearTextBox(log);
		parse_dot_file(std::string(CurrentDocPath.mbc_str()));
	}

	OpenDialog->Destroy();
}

void MainWindow::parse_dot_file(std::string filename) {

	unsigned num_edges = 0;
	unsigned num_nodes = 0;
	unsigned paths_added = 0;
	unsigned paths_removed = 0;
	std::string line;
	std::ifstream file(filename);
	std::regex node_regex("\"[0-9]+\" \\[label=");
	std::regex edge_regex("->");
	std::regex path_add_regex("V2::Branch");
	std::regex path_sub_regex("V1::Branch");
	if (file.is_open()) {

		while (std::getline(file, line)) {
			if (std::regex_search(line, node_regex)) {
				num_nodes += 1;
			}
			if (std::regex_search(line, edge_regex)) {
				num_edges += 1;
			}
			if (std::regex_search(line, path_add_regex)) {
				paths_added += 1;
			}
			if (std::regex_search(line, path_sub_regex)) {
				paths_removed += 1;
			}
		}
	}
        clearTextBox(log);
	addTextToTextBox(log, "Number of Nodes: " + std::to_string(num_nodes));
	addTextToTextBox(log, "\nNumber of Edges: " + std::to_string(num_edges));
	addTextToTextBox(log, "\nPaths added: " + std::to_string(paths_added/2));
	addTextToTextBox(log, "\nPaths removed: " + std::to_string(paths_removed/2)+ "\n");
}

void MainWindow::addTextToTextBox(wxTextCtrl *textBox, std::string str) {

        wxString wxStr(str.c_str(), wxConvUTF8);
	textBox->Freeze();
	textBox->AppendText(wxStr);
	textBox->Thaw();
}

void MainWindow::clearTextBox(wxTextCtrl *textBox) {
	const int numOfLines = textBox->GetNumberOfLines();
	for (int i = 0; i < numOfLines; ++i) {
		long length = textBox->GetLineLength(i);
		textBox->Remove(0, length);
	}
}
