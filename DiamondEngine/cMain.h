#ifndef _cmain_
#define _cmain_
#pragma once
//Images
#include "Images/Icons/addBlock.xpm"
//WxWidgets
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/splitter.h"
#include "wx/artprov.h"
//Render
#include "Render.h"
//Cg Types
#include "cg.h"
//ID's
#include "IDs.h"


#define DEFAULT_WINDOW_WIDTH 870
#define DEFAULT_WINDOW_HEIGHT 635


class cMain;
class cLogFrame;


class cMain : public wxFrame
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
	cLogFrame() : wxFrame(NULL, wxID_ANY, _("Console")) {
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
#endif