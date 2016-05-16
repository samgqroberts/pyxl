#include "RippleAnimation.h"
using namespace std;

RippleAnimation* RippleAnimation::create(
  long numLines,
  long numCols,
  long startTime,
  long duration
) {
  return new RippleAnimation(
    numLines,
    numCols,
    startTime,
    duration,
    numCols + 1
  );
}

void RippleAnimation::applyFrame(vector<vector<PixelState> >* canvas, long frame) {
  // off column
  if ( frame < maxFrames ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvas->at(l)[frame] = OFF;
    }
  }
  // on column
  if ( frame >= 1 ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvas->at(l)[frame - 1] = ON;
    }
  }
}

/**
 * First frame: 1st column is off
 * Second frame: 1st column on, 2nd off
 * Third frame: 2nd column on, 3rd off
 * ...
 * Second to last frame: last column is off, 2nd to last column is on
 * Last frame: last column is on
 */
vector<vector<PixelState> >* RippleAnimation::computeFrame(long currentTime) {
  long currentFrame = (currentTime - startTime) / frameDuration;
  vector<long> applicableFrames = getApplicableFrames(currentFrame);
  if (applicableFrames.size() == 0) {
    return nullptr;
  }
  vector<vector<PixelState> >* canvas = getBlankFrameState();
  for (int i = 0; i < applicableFrames.size(); i++) {
    applyFrame(canvas, applicableFrames[i]);
  }
  return canvas;
}
