#include "cApp.h"
#include <stdlib.h>
BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)
EVT_MOTION(BasicGLPane::mouseMoved)
EVT_LEFT_DOWN(BasicGLPane::mouseDown)
EVT_LEFT_UP(BasicGLPane::mouseReleased)
EVT_RIGHT_DOWN(BasicGLPane::rightClick)
EVT_RIGHT_UP(BasicGLPane::rightReleased)
EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
EVT_SIZE(BasicGLPane::resized)
EVT_KEY_DOWN(BasicGLPane::keyPressed)
EVT_KEY_UP(BasicGLPane::keyReleased)
EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
EVT_PAINT(BasicGLPane::onPaint)
END_EVENT_TABLE()
void BasicGLPane::keyReleased(wxKeyEvent& event) {}
void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) {}
void BasicGLPane::mouseLeftWindow(wxMouseEvent& event) {}
void BasicGLPane::mouseReleased(wxMouseEvent& event) {}

wxIMPLEMENT_APP(cApp);
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_TOOL(ADD_BLOCK_ID, cApp::AddBlock)
wxEND_EVENT_TABLE()



//Window
glm::vec2 winSize;


//Textures
Texture Tex[7];
enum { SUS, BRICK, WOOD, METAL, WOODBOX, WORLD, RICARDO };
string textures_files_names[7] = { "sus.png", "brickTexture.jpg", "woodTexture.jpg", "metalTexture.jpg", "woodBoxTexture.png", "worldTexture.jpg", "ricardoTexture.png" };


//Loader
Loader* loader = new Loader(10, Tex);


//Hitbox
bool debugHitbox = true;


//Camera
Camera camera;
bool cameraShouldMove = false;


//Mouse
Mouse mouse(camera);
glm::vec2 lastMousePos;
bool  firstTimeMouse = true;



bool cApp::OnInit() {
    render_loop_on = true;

    m_frame1 = new cMain();
    m_frame1->Show();

    //Console
    (new cLogFrame())->Show();
    
    //char buffer[64];
    //snprintf(buffer, sizeof buffer, "%f", m_frame1->);
    //wxLogMessage(buffer);
    return true;
}



void cApp::AddBlock(wxCommandEvent& event) {
    static float nextBlockPos = 0.0;

    event.Skip();

    Texture* wood_tex = &Tex[WOOD];
    Texture* woodBox_tex = &Tex[WOODBOX];
    Texture* sus_tex = &Tex[SUS];

    loader->LoadCube(CUBE_DEFAULT_SIZE * 1, glm::vec3(0.0, 0.0 + nextBlockPos, 0.0), woodBox_tex);
    nextBlockPos+= CUBE_DEFAULT_SIZE;
}




BasicGLPane::BasicGLPane(wxPanel* parent, int* args) : wxGLCanvas(parent, BASICGLPANE_ID, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE | wxWS_EX_PROCESS_IDLE) {
    m_context = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    if (!IsShown()) return;
    SetCurrent(*m_context);

    winSize.x = parent->GetSize().x;
    winSize.y = parent->GetSize().y;

    //Load texture
    loader->LoadTextures(textures_files_names);

    //Load objects
    loader->GenerateRandom();
    loader->LoadObj("stall.obj", glm::vec3(10.0, 0.0, 0.0));
}



void BasicGLPane::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // Textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(topleft_x, topleft_y, bottomrigth_x - topleft_x, bottomrigth_y - topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void BasicGLPane::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glViewport(topleft_x, topleft_y, bottomrigth_x - topleft_x, bottomrigth_y - topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio_w_h = (float)(bottomrigth_x - topleft_x) / (float)(bottomrigth_y - topleft_y);
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void BasicGLPane::keyPressed(wxKeyEvent& event) {
    wxChar uk = event.GetUnicodeKey();
    if (uk != WXK_NONE) {
        switch (uk) {
            case 0x0057:
                camera.forward();
                break;
            case 0x0053:
                camera.back();
                break;
            case 0x0041:
                camera.left();
                break;
            case 0x0044:
                camera.right();
                break;
            case 0x0045:
                camera.up();
                break;
            case 0x0051:
                camera.down();
                break;
        }
    }
}



void BasicGLPane::mouseMoved(wxMouseEvent& event) {
    static float acceleration = 0;
    static float limit = 1;
    int x = event.GetX(), y = event.GetY();
    float dx, dy;

    if (firstTimeMouse) {
        dx = 0;
        dy = 0;
        lastMousePos.x = x;
        lastMousePos.y = y;
        firstTimeMouse = false;
    }
    dx = x - lastMousePos.x;
    dy = y - lastMousePos.y;
    lastMousePos.x = x;
    lastMousePos.y = y;

    //Every time mouse moves i update Mouse.m_pos value with Mouse->setPos() method
    mouse.setPos(glm::vec2(x, y));

    if (cameraShouldMove) {
        if (acceleration < limit) {
            acceleration+= 0.05;
        }
        camera.updateYaw(dx * acceleration, ((dy * acceleration) / (PI / 2)));
        camera.update();
    }
    else {
        acceleration = 0;
    }
}
void BasicGLPane::mouseDown(wxMouseEvent& event) {
    glm::vec3 ep = mouse.toEyeSpace();
    glm::vec3 wp = mouse.toWorldSpace(ep);

    Texture* sus_tex = &Tex[SUS];
    loader->LoadCube(0.2, wp, sus_tex);
    //loader->LoadHitbox(debugHitbox, loader->getObject(loader->ObjectsTotal() - 2), loader->getLastObject());
    //loader->LoadLine(camera.m_pos, realPos);

    char buffer[64];
    snprintf(buffer, sizeof buffer, "mouseX: %.4f mouseY: %.4f pos: (%.4f, %.4f, %.4f)", mouse.pos.x, mouse.pos.y, wp.x, wp.y, wp.z);
    wxLogMessage(buffer);
}
void BasicGLPane::rightClick(wxMouseEvent& event) {
    cameraShouldMove = true;
}
void BasicGLPane::rightReleased(wxMouseEvent& event) {
    cameraShouldMove = false;
}



void BasicGLPane::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glPushMatrix();

    prepare3DViewport(0, 0, getWidth(), getHeight());
    glLoadIdentity();


    //Activates the camera
    camera.activate();


    //Setup everything
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);


    //Light and material
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float globalAmb[] = { 0.1f, 0.1f, 0.1f, 1.f };
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);
    float light0[4][4] = {
            { 0.1f, 0.1f, 0.1f, 1.f}, // Ambient
            { 0.8f, 0.8f, 0.8f, 1.f}, // Diffuse
            { 1.f,   1.f,  1.f, 1.f}, // Specular
            { 0.f,   0.f,  1.f, 1.f}  // Position
    };
    glLightfv(GL_LIGHT0, GL_AMBIENT,  &light0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  &light0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);


    //Objects
    loader->DrawEverything();


    camera.updateYaw(0, 0 / (PI / 2));
    camera.update();


    //Disable and end everything
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPopMatrix();
    glFlush();
    SwapBuffers();
}



void BasicGLPane::onPaint(wxPaintEvent& evt) {
    wxPaintDC dc(this);
    render();
}