#ifndef DIMENCO_H
#define DIMENCO_H

#include <GL/GL.H>
#include <Windows.h>
#include <assert.h>


static bool API_Available = false;
typedef void (*SIGNALZBUFFERAVAILABLEPTR)();
typedef void (*SIGNALBACKGROUNDAVAILABLEPTR)(BOOL, BOOL);
typedef BOOL (*ENABLE3DMODEPTR)(BOOL);
typedef BOOL (*SETRENDERINGPARAMETERSPTR)(int, int, int, int, BOOL, BOOL, float,
                                          float, float);
typedef BOOL (*SELECTFORMATPTR)(int);
typedef BOOL (*SETAPPLICATIONRESOLUTIONPTR)(int, int);
typedef BOOL (*SETINPUTRESOLUTIONPTR)(int, int);
typedef BOOL (*SETVIDEOWALLBEZELSIZEPTR)(float, float);

static SIGNALZBUFFERAVAILABLEPTR SignalZBufferAvailable = NULL;
static SIGNALBACKGROUNDAVAILABLEPTR SignalBackgroundAvailable = NULL;
static ENABLE3DMODEPTR Enable3DMode = NULL;
static SETRENDERINGPARAMETERSPTR SetRenderingParameters = NULL;
static SELECTFORMATPTR SelectFormat = NULL;
static SETAPPLICATIONRESOLUTIONPTR SetApplicationResolution = NULL;
static SETINPUTRESOLUTIONPTR SetInputResolution = NULL;
static SETVIDEOWALLBEZELSIZEPTR SetVideoWallBezelSize = NULL;

static void dimencoInit(void) {
  // bool API_Available = true;

  // Retrieve function pointers to the 3DS OpenGL Interface API functions
  HMODULE hOpenGLDll = GetModuleHandle(TEXT("opengl32.dll"));

  SignalZBufferAvailable = (SIGNALZBUFFERAVAILABLEPTR)GetProcAddress(
      hOpenGLDll, "SignalZBufferAvailable");
  SignalBackgroundAvailable = (SIGNALBACKGROUNDAVAILABLEPTR)GetProcAddress(
      hOpenGLDll, "SignalBackgroundAvailable");
  Enable3DMode = (ENABLE3DMODEPTR)GetProcAddress(hOpenGLDll, "Enable3DMode");
  SetRenderingParameters = (SETRENDERINGPARAMETERSPTR)GetProcAddress(
      hOpenGLDll, "SetRenderingParameters");
  SelectFormat = (SELECTFORMATPTR)GetProcAddress(hOpenGLDll, "SelectFormat");
  SetApplicationResolution = (SETAPPLICATIONRESOLUTIONPTR)GetProcAddress(
      hOpenGLDll, "SetApplicationResolution");
  SetInputResolution =
      (SETINPUTRESOLUTIONPTR)GetProcAddress(hOpenGLDll, "SetInputResolution");
  SetVideoWallBezelSize = (SETVIDEOWALLBEZELSIZEPTR)GetProcAddress(
      hOpenGLDll, "SetVideoWallBezelSize");

  if (!SignalZBufferAvailable) {
    return;
    // Implement output of error message
  } else
    API_Available = true;

  assert(SignalZBufferAvailable);
  assert(SignalBackgroundAvailable);
  assert(Enable3DMode);
  assert(SetRenderingParameters);
  assert(SelectFormat);
  assert(SetApplicationResolution);
  assert(SetInputResolution);

  if (API_Available) {
    if (!SetVideoWallBezelSize) {
      // Implement output of error message
    } else {
      // uncomment to override the bezel size from visualizer.ini
      // SetVideoWallBezelSize(0.0,0.0); // Set bezelsize X,Y to 0,0 by default
    }
  }

#define FORMAT_2D_PLUS_DEPTH                                                   \
  0 // This is the default if SelectFormat is not called
#define FORMAT_DECLIPSE 1

  if (API_Available)
    SelectFormat(FORMAT_DECLIPSE);
  // assert(SetApplicationResolution(1920,1080));
  assert(SetInputResolution(2560, 1440));
}

static void dimencoInitState(void) {
  // bool API_Available = true;

  // Set some non-default rendering parameters
  if (API_Available)
    SetRenderingParameters(
        64,      // factor
        128,     // content creator offset
        2,       // horizontal morphological filter
        2,       // vertical morphological filter
        TRUE,    // cyclic view
        TRUE,    // use inverse projection
        0.0f,    // near interest Z-buffer value
        1.0f,    // far interest Z-buffer value
        100.0f); // far/near ratio (ignored because inverse projection is used)
}

static void dimencoSetBackgroundState(void) {
  // bool API_Available = true;

  if (API_Available)
    SignalBackgroundAvailable(TRUE, TRUE);
}

static void dimencoSetZBufState(void) {
  // bool API_Available = true;

  // This shows how SignalZBufferAvailable() can be used to make sure the
  // OpenGL Interface uses the right depth information even if the application
  // clears or overwrites the Z-buffer before calling SwapBuffers.

  if (API_Available)
    SignalZBufferAvailable();
  if (API_Available)
    glClear(GL_DEPTH_BUFFER_BIT);
}

#endif // DIMENCO_H