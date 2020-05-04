#include "MainWindow.h"
//Coords for right and left side of window
#define RIGHT 140
#define LEFT 50
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
	menuFile->Append(1, "&Help...\tCtrl-H",
					"Redirects to hydrogui git repository");
	menuConsole->Append(2, "&Run Hydrogen..\tCtrl-H",
					"Run Hydrogen and transfer dotfile");
	menuConsole->Append(8,"&Clean Remote Files..\tCtrl-G",
					"Delete remote files");						 
	
	menuBar->Append(menuFile, "About");
	menuBar->Append(menuConsole, "Console");
    SetMenuBar( menuBar );

	wxPanel* panel = new wxPanel(this);


	 			
    wxTextCtrl *text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10,10), wxSize(140, 30), 0,
					  wxDefaultValidator, wxTextCtrlNameStr);


    wxButton* graphBtn = new wxButton(panel, 4, "Select MVICFG", wxPoint(10,50),wxSize(125, 50));
    Bind(wxEVT_BUTTON, &MainWindow::SelectMVICFG, this, 4);
    wxButton* buggyBtn = new wxButton(panel, 5, "Select Buggy Files", wxPoint(RIGHT,50),wxSize(150, 50));
    wxButton* fixedBtn = new wxButton(panel, 6, "Select Fixed Files", wxPoint(RIGHT,100),wxSize(150, 50));
	
	// wxButton* showFiles = new wxButton(panel, 7, "List files", wxPoint(RIGHT,150),wxSize(150, 50));
	
	
	
	Bind(wxEVT_BUTTON, &MainWindow::selectSource, this, 5);
	Bind(wxEVT_BUTTON, &MainWindow::selectFixed, this, 6);
	// Bind(wxEVT_BUTTON, &MainWindow::ListBuggyAndFixedFiles, this, 7);
	// wxButton* btn = new wxButton(panel, wxID_ANY, "Button", wxPoint(250,100),wxSize(100, 50));
	
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

	int i, j;
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
		std::cout << "Here" << std::endl;
		wxArrayString CurrentDocPaths;
		OpenDialog->GetPaths(buggyFilesAbsolute);
		OpenDialog->GetFilenames(buggyFileNames);
		std::cout << CurrentDocPaths.GetCount() << std::endl;
		int count = CurrentDocPaths.GetCount();
		int i;
		for(i=0; i<count; i++){
			std::cout << "Added Buggy File(s): " <<CurrentDocPaths.Item(i) << std::endl;
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
		std::cout << "Here" << std::endl;
		wxArrayString CurrentDocPaths;
		OpenDialog->GetPaths(CurrentDocPaths);
		OpenDialog->GetPaths(fixedFilesAbsolute);
		OpenDialog->GetFilenames(fixedFileNames);
		std::cout << CurrentDocPaths.GetCount() << std::endl;
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
			// std::cout << "fixed["<<i<<"]:" << fixedFiles.Item(i) << std::endl;
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
		// OpenDialog->GetPaths(buggyFilesAbsolute);
		// OpenDialog->GetFilenames(buggyFileNames);
		// Sets our current document to the file the user selected
		system("xdot " + CurrentDocPath);
	}

	// Clean up after ourselves
	OpenDialog->Destroy();
}
