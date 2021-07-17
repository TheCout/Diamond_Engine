#pragma once
#include "Images/Icons/addBlock.xpm"
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/splitter.h"
#include "wx/artprov.h"
#include "Render.h"
#include "cg.h"
#include "IDs.h"


class Configurations
{
protected:
	static const int WINDOW_WIDTH = 870;
	static const int WINDOW_HEIGHT = 635;
};



class cMain : public wxFrame, public Configurations
{
	RenderTimer* timer;
	GLPane* wxgl;

public:
	cMain();
	~cMain();

public:

	//Splitters
	wxSplitterWindow* splitter = nullptr;
	wxSplitterWindow* right_splitter = nullptr;

	//Panels
	wxPanel*  left = nullptr;
	wxPanel* right = nullptr;
	wxPanel* bottom = nullptr;

	//Hierarchy
	wxListBox* hierarchy = nullptr;

	//Menu bar
	wxMenuBar* menubar;
	wxMenu* menu;

	//Tool bar
	wxToolBar* toolbar;

	//Button
	wxButton **btn;
	bool bFirstClick = true;

	void onQuit(wxCommandEvent& WXUNUSED(event));
	void RightClick(wxCommandEvent& event);
	void AddBlock(wxCommandEvent& event);
	void GLPaneResized(wxCommandEvent& event);
	DECLARE_EVENT_TABLE();
};



class cLogFrame : public wxFrame
{
public:
	cLogFrame() : wxFrame(NULL, wxID_ANY, _("Console")) 
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

		wxTextCtrl* logText = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxSize(750, 500), wxTE_MULTILINE | wxTE_READONLY);

		wxFont myFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

		
		logText->SetFont(myFont);
		sizer->Add(logText, 1, wxEXPAND, 5);
		SetSizer(sizer);

		wxLog::SetTimestamp("");
		wxLog::SetActiveTarget(new wxLogTextCtrl(logText));
	}
};