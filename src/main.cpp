#include "ofApp.h"
#include "ofMain.h"

int main() {
#ifdef USE_DIMENCO_OPENGL_INTERFACE
  ofAppGLFWWindow win;
  win.setMultiDisplayFullscreen(true);
  ofSetupOpenGL(&win, 640, 480, OF_FULLSCREEN);
#else
  ofSetupOpenGL(1600, 900, OF_WINDOW);
#endif
  ofRunApp(new ofApp());
}
