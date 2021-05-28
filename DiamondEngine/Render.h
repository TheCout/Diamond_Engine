#ifndef _render_
#define _render_
#pragma once
#include "wx/sizer.h"
#include "wx/timer.h"
#include "GLpane.h"

class RenderTimer : public wxTimer {
    GLPane* pane;
public:
    RenderTimer(GLPane* pane);
    void Notify();
    void start();
};
#endif