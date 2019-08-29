// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"

#include "ParticleSystem.h"

class ofApp : public ofBaseApp
   {
   public:
      ofApp();

      void setup();
      void update();
      void draw();

      void keyPressed(int key);
      void keyReleased(int key);
      void mouseMoved(int x, int y);
      void mouseDragged(int x, int y, int button);
      void mousePressed(int x, int y, int button);
      void mouseReleased(int x, int y, int button);
      void mouseEntered(int x, int y);
      void mouseExited(int x, int y);
      void windowResized(int w, int h);
      void dragEvent(ofDragInfo dragInfo);
      void gotMessage(ofMessage msg);

   private:
      void RandomizeParticlesInteraction();

      ParticleSystem mParticleSystem;

      bool mPaused;
   };

#endif
