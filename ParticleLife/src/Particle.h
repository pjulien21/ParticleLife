// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"

class Particle
   {
   public:
      Particle(const ParticleType& particleType,
               const float         posX,
               const float         posY,
               const float         speedX,
               const float         speedY);

      ofColor Color() const noexcept
         {
         return mParticleType->Color();
         }

      float PosX() const noexcept
         {
         return mPosX;
         }

      float PosY() const noexcept
         {
         return mPosY;
         }

      float SpeedX() const noexcept
         {
         return mSpeedX;
         }

      float SpeedY() const noexcept
         {
         return mSpeedY;
         }

      const ParticleType& Type() const
         {
         return (*mParticleType);
         }

      void SetPosX(const float posX) noexcept
         {
         mPosX = posX;
         }

      void SetPosY(const float posY) noexcept
         {
         mPosY = posY;
         }

      void SetSpeedX(const float speedX) noexcept
         {
         mSpeedX = speedX;
         }

      void SetSpeedY(const float speedY) noexcept
         {
         mSpeedY = speedY;
         }

   private:
      const ParticleType* mParticleType;

      float mPosX;
      float mPosY;
      float mSpeedX;
      float mSpeedY; 
   };

#endif
