#include "Render.h"


RenderTimer::RenderTimer(GLPane* pane) : wxTimer() {
    RenderTimer::pane = pane;
}

void RenderTimer::Notify() {
    pane->Refresh();
}

void RenderTimer::start() {
    wxTimer::Start(10);
}