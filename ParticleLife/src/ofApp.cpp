// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

#include <random>

namespace Constants
   {
   constexpr int NB_FRAMES_PER_SECOND = 30;
   constexpr char* WINDOW_TITLE = "ParticleLife";
   };

//--------------------------------------------------------------
ofApp::ofApp()
   : mPaused(false)
   {

   }

//--------------------------------------------------------------
void ofApp::setup()
   {
   ofSetWindowTitle(Constants::WINDOW_TITLE);
   ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);

   std::random_device rd;
   std::mt19937 RandomEngine(rd());

                             // Create particles types
   mParticleSystem.CreateParticleType("Blue", ofColor::blue);
   mParticleSystem.CreateParticleType("Green", ofColor::green);
   mParticleSystem.CreateParticleType("Orange", ofColor::darkorange);
   mParticleSystem.CreateParticleType("Red", ofColor::red);
   mParticleSystem.CreateParticleType("Yellow", ofColor::yellow);

                             // Setup particles interaction
   RandomizeParticlesInteraction();

                             // Create particles
   std::uniform_int_distribution<int> randomNb(75, 100);

   mParticleSystem.CreateParticle("Blue", randomNb(RandomEngine));
   mParticleSystem.CreateParticle("Green", randomNb(RandomEngine));
   mParticleSystem.CreateParticle("Orange", randomNb(RandomEngine));
   mParticleSystem.CreateParticle("Red", randomNb(RandomEngine));
   mParticleSystem.CreateParticle("Yellow", randomNb(RandomEngine));
   }

//--------------------------------------------------------------
void ofApp::RandomizeParticlesInteraction()
   {
   std::random_device rd;
   std::mt19937 RandomEngine(rd());

   std::normal_distribution<float> randomForce(0.02f /*mean*/,  0.04f /*sigma*/);

   for (const ParticleType* particleType : mParticleSystem.ParticleTypes())
      {
      for (const ParticleType* otherParticleType : mParticleSystem.ParticleTypes())
         {
         mParticleSystem.SetInteractForce(particleType->Name(),
                                          otherParticleType->Name(),
                                          randomForce(RandomEngine));
         }
      }
   }

//--------------------------------------------------------------
void ofApp::update()
   {
   if (!mPaused)
      mParticleSystem.Update();
   }

//--------------------------------------------------------------
void ofApp::draw()
   {
   ofClear(ofColor::black);

   mParticleSystem.Render();
   }

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
   {

   }

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
   {
   switch (key)
      {
      case ' ':
         {
         mPaused = !mPaused;
         break;
         }
      case 'r':
      case 'R':
         {
                             // Randomize
         RandomizeParticlesInteraction();
         break;
         }
      case '1':
         {
                             // Ladybug
         mParticleSystem.SetInteractForce("Blue", "Blue", -0.0230621f);
         mParticleSystem.SetInteractForce("Blue", "Green", 0.0021758f);
         mParticleSystem.SetInteractForce("Blue", "Orange", 0.0312983f);
         mParticleSystem.SetInteractForce("Blue", "Red", 0.169501f);
         mParticleSystem.SetInteractForce("Blue", "Yellow", 0.00484047f);

         mParticleSystem.SetInteractForce("Green", "Blue", -0.0409867f);
         mParticleSystem.SetInteractForce("Green", "Green", 0.0135509f);
         mParticleSystem.SetInteractForce("Green", "Orange", 0.0322179f);
         mParticleSystem.SetInteractForce("Green", "Red", 0.035552f);
         mParticleSystem.SetInteractForce("Green", "Yellow", 0.0f);

         mParticleSystem.SetInteractForce("Orange", "Blue", 0.023678f);
         mParticleSystem.SetInteractForce("Orange", "Green", -0.00294422f);
         mParticleSystem.SetInteractForce("Orange", "Orange", 0.0581442f);
         mParticleSystem.SetInteractForce("Orange", "Red", 0.00317007f);
         mParticleSystem.SetInteractForce("Orange", "Yellow", 0.0408892f);

         mParticleSystem.SetInteractForce("Red", "Blue", 0.066107f);
         mParticleSystem.SetInteractForce("Red", "Green", -0.0309665f);
         mParticleSystem.SetInteractForce("Red", "Orange", 0.0114481f);
         mParticleSystem.SetInteractForce("Red", "Red", -0.014513f);
         mParticleSystem.SetInteractForce("Red", "Yellow", 0.0321005f);

         mParticleSystem.SetInteractForce("Yellow", "Blue", 0.0839062f);
         mParticleSystem.SetInteractForce("Yellow", "Green", 0.0037805f);
         mParticleSystem.SetInteractForce("Yellow", "Orange", -0.0108229f);
         mParticleSystem.SetInteractForce("Yellow", "Red", -0.0382133f);
         mParticleSystem.SetInteractForce("Yellow", "Yellow", 0.0377844f);
         break;
         }
      case '2':
         {
                             // Planets
         mParticleSystem.SetInteractForce("Blue", "Blue", 0.0582505f);
         mParticleSystem.SetInteractForce("Blue", "Green", 0.0563729f);
         mParticleSystem.SetInteractForce("Blue", "Orange", 0.0609637f);
         mParticleSystem.SetInteractForce("Blue", "Red", 0.0344184f);
         mParticleSystem.SetInteractForce("Blue", "Yellow", 0.0661463f);

         mParticleSystem.SetInteractForce("Green", "Blue", 0.0504253f);
         mParticleSystem.SetInteractForce("Green", "Green", -0.00571114f);
         mParticleSystem.SetInteractForce("Green", "Orange", 0.0256715f);
         mParticleSystem.SetInteractForce("Green", "Red", 0.0722679f);
         mParticleSystem.SetInteractForce("Green", "Yellow", 0.0421896f);

         mParticleSystem.SetInteractForce("Orange", "Blue", 0.0689674f);
         mParticleSystem.SetInteractForce("Orange", "Green", 0.10057f);
         mParticleSystem.SetInteractForce("Orange", "Orange", -0.00667134f);
         mParticleSystem.SetInteractForce("Orange", "Red", 0.039501f);
         mParticleSystem.SetInteractForce("Orange", "Yellow", -0.0219484f);

         mParticleSystem.SetInteractForce("Red", "Blue", 0.0417152f);
         mParticleSystem.SetInteractForce("Red", "Green", -0.0410326f);
         mParticleSystem.SetInteractForce("Red", "Orange", 0.0894822f);
         mParticleSystem.SetInteractForce("Red", "Red", 0.0548828f);
         mParticleSystem.SetInteractForce("Red", "Yellow", 0.037825f);

         mParticleSystem.SetInteractForce("Yellow", "Blue", 0.0317165f);
         mParticleSystem.SetInteractForce("Yellow", "Green", 0.0442207f);
         mParticleSystem.SetInteractForce("Yellow", "Orange", 0.04717f);
         mParticleSystem.SetInteractForce("Yellow", "Red", 0.04717f);
         mParticleSystem.SetInteractForce("Yellow", "Yellow", -0.00536005f);
         break;
         }
      case '3':
         {
                             // Spooky clowns
         mParticleSystem.SetInteractForce("Blue", "Blue", -0.0360085f);
         mParticleSystem.SetInteractForce("Blue", "Green", -0.0335847f);
         mParticleSystem.SetInteractForce("Blue", "Orange", -0.00462437f);
         mParticleSystem.SetInteractForce("Blue", "Red", 0.0200793f);
         mParticleSystem.SetInteractForce("Blue", "Yellow", 0.0757241f);

         mParticleSystem.SetInteractForce("Green", "Blue", 0.00740106f);
         mParticleSystem.SetInteractForce("Green", "Green", 0.0597985f);
         mParticleSystem.SetInteractForce("Green", "Orange", -0.0149999f);
         mParticleSystem.SetInteractForce("Green", "Red", 0.0105064f);
         mParticleSystem.SetInteractForce("Green", "Yellow", -0.0624585f);

         mParticleSystem.SetInteractForce("Orange", "Blue", -0.0148173f);
         mParticleSystem.SetInteractForce("Orange", "Green", -0.0472571f);
         mParticleSystem.SetInteractForce("Orange", "Orange", 0.0348452f);
         mParticleSystem.SetInteractForce("Orange", "Red", 0.0570931f);
         mParticleSystem.SetInteractForce("Orange", "Yellow", 0.0168622f);

         mParticleSystem.SetInteractForce("Red", "Blue", 0.0384952f);
         mParticleSystem.SetInteractForce("Red", "Green", 0.0262993f);
         mParticleSystem.SetInteractForce("Red", "Orange", 0.0555763f);
         mParticleSystem.SetInteractForce("Red", "Red", 0.0923495f);
         mParticleSystem.SetInteractForce("Red", "Yellow", -0.0105489f);

         mParticleSystem.SetInteractForce("Yellow", "Blue", -0.0221582f);
         mParticleSystem.SetInteractForce("Yellow", "Green", 0.0471038f);
         mParticleSystem.SetInteractForce("Yellow", "Orange", 0.0374017f);
         mParticleSystem.SetInteractForce("Yellow", "Red", 0.0768879f);
         mParticleSystem.SetInteractForce("Yellow", "Yellow", -0.0115467f);
         break;
         }
      case '4':
         {
                             // Jewels
         mParticleSystem.SetInteractForce("Blue", "Blue", -0.0599394f);
         mParticleSystem.SetInteractForce("Blue", "Green", 0.0288017f);
         mParticleSystem.SetInteractForce("Blue", "Orange", 0.00408687f);
         mParticleSystem.SetInteractForce("Blue", "Red", -0.0366389f);
         mParticleSystem.SetInteractForce("Blue", "Yellow", -0.0831787f);

         mParticleSystem.SetInteractForce("Green", "Blue", 0.0224548f);
         mParticleSystem.SetInteractForce("Green", "Green", 0.03671f);
         mParticleSystem.SetInteractForce("Green", "Orange", 0.0201453f);
         mParticleSystem.SetInteractForce("Green", "Red", 0.0275762f);
         mParticleSystem.SetInteractForce("Green", "Yellow", -0.00215059f);

         mParticleSystem.SetInteractForce("Orange", "Blue", 0.004772f);
         mParticleSystem.SetInteractForce("Orange", "Green", 0.0690149f);
         mParticleSystem.SetInteractForce("Orange", "Orange", 0.0553937f);
         mParticleSystem.SetInteractForce("Orange", "Red", 0.0296576f);
         mParticleSystem.SetInteractForce("Orange", "Yellow", 0.0212732f);

         mParticleSystem.SetInteractForce("Red", "Blue", 0.0747139f);
         mParticleSystem.SetInteractForce("Red", "Green", -0.0763053f);
         mParticleSystem.SetInteractForce("Red", "Orange", -0.00733691f);
         mParticleSystem.SetInteractForce("Red", "Red", 0.0409483f);
         mParticleSystem.SetInteractForce("Red", "Yellow", 0.0306649f);

         mParticleSystem.SetInteractForce("Yellow", "Blue", 0.0196015f);
         mParticleSystem.SetInteractForce("Yellow", "Green", 0.0597547f);
         mParticleSystem.SetInteractForce("Yellow", "Orange", -0.0875641f);
         mParticleSystem.SetInteractForce("Yellow", "Red", 0.0176012f);
         mParticleSystem.SetInteractForce("Yellow", "Yellow", -0.0357769f);
         break;
         }
      }
   }

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
   {

   }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
   {

   }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
   {

   }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
   {

   }

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
   {

   }

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
   {

   }

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
   {

   }

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
   {

   }

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
   {

   }
