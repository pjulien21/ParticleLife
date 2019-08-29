// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <map>
#include <string>

#include "ofMain.h"

class ParticleType
   {
   public:
      ParticleType(const std::string& Name,
                   const ofColor& Color);

      const ofColor& Color() const;

      const std::string& Name() const;

      float InteractionForce(const ParticleType& other) const;
      void SetInteractionForce(const ParticleType& other,
                               const float Force);

      std::map<std::string, float> ParticleInteractionMap() const;

   private:
      ofColor mColor;
      std::string mName;

      std::map<std::string, float> mParticleInteractionMap;
   };

#endif
