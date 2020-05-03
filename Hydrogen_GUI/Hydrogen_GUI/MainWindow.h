#pragma once
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
class MainWindow : public wxFrame
{
public:
	MainWindow(wxWindow *parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxFrameNameStr);
		wxArrayString buggyFilesAbsolute;
		wxArrayString fixedFilesAbsolute;
		wxArrayString fixedFileNames;
		wxArrayString buggyFileNames;
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void SelectMVICFG(wxCommandEvent& WXUNUSED(event));
	void OnExec(wxCommandEvent& event);
	void generateGraph();
	wxArrayString doExecute(wxString& cmd);
	void ListBuggyAndFixedFiles();
	void selectSource(wxCommandEvent& WXUNUSED(event));
	void selectFiles(int MODE);
	void selectFixed (wxCommandEvent& WXUNUSED(event));
	void TransferBuggyAndFixedFiles();
	~MainWindow();
};

