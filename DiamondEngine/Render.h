#pragma once
#include "wx/sizer.h"
#include "wx/timer.h"
#include "opengl.h"

class RenderTimer : public wxTimer {
    BasicGLPane* pane;
public:
    RenderTimer(BasicGLPane* pane);
    void Notify();
    void start();
};