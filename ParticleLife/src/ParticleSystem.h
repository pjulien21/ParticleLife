// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Particle.h"
#include "ParticleType.h"

class ParticleSystem
   {
   public:
      ParticleSystem();

      bool CreateParticle(const std::string& ParticleTypeName,
                          const int Nb = 1);

      bool CreateParticleType(const std::string& Name,
                              const ofColor& Color);

      bool SetInteractForce(const std::string& ParticleTypeName,
                            const std::string& OtherParticleTypeName,
                            const float Force);

      std::vector<ParticleType*> ParticleTypes();

      void Render() const;
      void Update();

   private:
      float InteractForce(const std::string& ParticleTypeName,
                          const std::string& OtherParticleTypeName) const;

      void UpdateParticlesPosition();
      void UpdateParticlesSpeed();

      const float mFriction;
      const float mMinParticleInteractionDistSquared;
      const float mMaxParticleInteractionDistSquared;
      const float mParticleInitialMaxSpeed;
      const float mParticleRadius;

                             // Cache for performance
      float mWindowHeight;
      float mWindowWidth;

                             // ParticleTypes
      std::map<std::string, ParticleType> mParticleTypesMap;

                             // Particles
      std::vector<Particle> mParticles = {};
   };

#endif
