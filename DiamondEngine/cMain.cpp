#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "DiamondEngine", wxPoint(30, 30), wxSize(Configurations::WINDOW_WIDTH, Configurations::WINDOW_HEIGHT)) {

	int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE , 16, 0 };
	wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);

	//Bitmaps
	wxBitmap addBlockBmp(addBlock_xpm);


	//Classes Definitions
	menubar = new wxMenuBar;
	menu = new wxMenu;
	splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	right_splitter = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	left = new wxPanel(splitter);
	right = new wxPanel(right_splitter);
	bottom = new wxPanel(right_splitter);
	wxgl = new GLPane(right, args);


	//Menu Bar
	menu->Append(wxID_EXIT, wxT("&Quit"));
	menubar->Append(menu, wxT("&File"));
	SetMenuBar(menubar);


	//Tool Bar
	toolbar = CreateToolBar();
	toolbar->AddTool(ADD_BLOCK_ID, _("AddBlock"), addBlockBmp);
	toolbar->Realize();


	//Splitters
	left->SetBackgroundColour(wxColor(45, 45, 45));
	right->SetBackgroundColour(wxColor(255,	105, 180));
	bottom->SetBackgroundColour(wxColor(45, 45, 45));
	right_splitter->SetMinimumPaneSize(150);
	right_splitter->SplitHorizontally(right, bottom);
	right_splitter->SetSashGravity(0);
	splitter->SetMinimumPaneSize(150);
	splitter->SplitVertically(left, right_splitter);
	splitter->SetSashGravity(0);


	//List
	wxString choices[] = {"     Part","Part", "Part"};
	hierarchy = new wxListBox(left, HIERARCHY_ID, wxDefaultPosition, GetClientSize(), sizeof(choices)/sizeof(*choices), choices, wxLB_SINGLE | wxLB_HSCROLL, wxDefaultValidator);
	hierarchy->SetBackgroundColour(wxColor(45, 45, 45));
	hierarchy->SetForegroundColour(wxColor(255, 255, 255));
	vsizer->Add(hierarchy, 1, wxEXPAND);
	left->SetSizer(vsizer);
	left->SetAutoLayout(true);
	left->Show();


	//OpenGL Frame/Panel
	wxgl->SetSize(right->GetSize());
	wxgl->SetMinSize(right->GetSize());
	hsizer->Add(wxgl, 1, wxEXPAND);
	right->SetSizer(hsizer);
	right->SetAutoLayout(true);
	right->Show();


	//Events
	Connect(wxID_EXIT, wxCommandEventHandler(cMain::onQuit));
	Connect(ADD_BLOCK_ID, wxEVT_TOOL, wxCommandEventHandler(cMain::AddBlock));


	//Timer
	timer = new RenderTimer(wxgl);
	Show();
	timer->start();
}



cMain::~cMain() {
	delete timer;
}


void cMain::RightClick(wxCommandEvent& event) {}
void cMain::AddBlock(wxCommandEvent& event) {
	event.Skip();
	wxString str[] = {"Part"};
	hierarchy->InsertItems(1, str, hierarchy->GetCount());
}


void cMain::onQuit(wxCommandEvent& WXUNUSED(event)) {
	timer->Stop();
	Close(true);
	abort();
}