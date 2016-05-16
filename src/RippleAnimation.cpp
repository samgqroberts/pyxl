#include "RippleAnimation.h"
using namespace std;

/**
 * First frame: 1st column is off
 * Second frame: 1st column on, 2nd off
 * Third frame: 2nd column on, 3rd off
 * ...
 * Second to last frame: last column is off, 2nd to last column is on
 * Last frame: last column is on
 */
vector<vector<PixelState> >* RippleAnimation::computeFrame(long currentTime) {
  logf("computeFrame");
  logf("\tcurrentTime: " + to_string(currentTime));
  float percentThrough = ((float) currentTime - (float) startTime) / duration;
  logf("\tpercentThrough: " + to_string(percentThrough));
  if (percentThrough >= 1) {
    return nullptr;
  }
  int maxFrames = numCols + 1;
  logf("\tmaxFrames: " + to_string(maxFrames));
  long frameDuration = duration / maxFrames;
  logf("\tframeDuration: " + to_string(frameDuration));
  int currentFrame = (currentTime - startTime) / frameDuration;
  logf("\tcurrentFrame: " + to_string(currentFrame));
  static vector<vector<PixelState> > canvasState (
    numLines,
    vector<PixelState> (numCols, IMPARTIAL)
  );
  // off column
  if ( currentFrame < maxFrames ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvasState[l][currentFrame] = OFF;
    }
  }
  // on column
  if ( currentFrame >= 1 ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvasState[l][currentFrame - 1] = ON;
    }
  }
  return &canvasState;
}