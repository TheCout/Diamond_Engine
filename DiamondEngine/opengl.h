#ifndef _glpane_
#define _glpane_

#include "wx/wx.h"
#include "wx/glcanvas.h"

#define BASICGLPANE_ID 0003

class BasicGLPane : public wxGLCanvas {
	wxGLContext* m_context;
public:
	wxPanel* panel;

	//Constructor and destructor
	BasicGLPane(wxPanel* parent, int* args);
	virtual ~BasicGLPane() { delete m_context; }

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