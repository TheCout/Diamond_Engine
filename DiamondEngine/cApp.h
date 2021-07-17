#pragma once
#include "wx/evtloop.h"
#include "cMain.h"
#include "Sound.h"
#include "Loader.h"
#include "Camera.h"
#include "Mouse.h"


#define CUBE_DEFAULT_SIZE 2.0
#define SPHERE_DEFAULT_SIZE 1.0
#define SPHERE_DEFAULT_DETAILING 20


class cApp : public wxApp {
	GLPane* glPane;
public:
	bool render_loop_on;
	cApp() {};
	~cApp() {};
	void AddBlock(wxCommandEvent& event);

private:
	cMain* m_frame1 = nullptr;
	cLogFrame* log_frame1 = nullptr;

public:
	virtual bool OnInit();
	wxFrame* frame;
};