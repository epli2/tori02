#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  ofAppGLFWWindow win;
  win.setMultiDisplayFullscreen(true);
  ofSetupOpenGL(&win, 640, 480, OF_FULLSCREEN);
#else
  ofSetupOpenGL(1600, 900, OF_WINDOW); // <-------- setup the GL context
#endif
  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new ofApp());
}
