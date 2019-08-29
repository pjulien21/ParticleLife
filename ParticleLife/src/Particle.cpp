// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "Particle.h"

#include "ofMain.h"

Particle::Particle(const ParticleType& particleType,
                   const float         posX,
                   const float         posY,
                   const float         speedX,
                   const float         speedY)
   : mParticleType(&particleType)
   , mPosX(posX)
   , mPosY(posY)
   , mSpeedX(speedX)
   , mSpeedY(speedY)
   {

   }
