#ifndef _glpane_
#define _glpane_
#pragma once

//WxWidgets
#include "wx/wx.h"
#include "wx/glcanvas.h"
//ID's
#include "IDs.h"


class GLPane : public wxGLCanvas {
	wxGLContext* m_context;
public:
	wxPanel* panel;

	//Constructor and destructor
	GLPane(wxPanel* parent, int* args);
	virtual ~GLPane() { delete m_context; }

	//Getters
	int getWidth() { return GetSize().x; }
	int getHeight() { return GetSize().y; }

	//Drawing
	void onPaint(wxPaintEvent& evt);
	void render();
	void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

	//Events
	void resized(wxSizeEvent& evt) { Refresh(); }
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void rightReleased(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	DECLARE_EVENT_TABLE()
};

#endif