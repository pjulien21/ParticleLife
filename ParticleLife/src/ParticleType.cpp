// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ParticleType.h"

ParticleType::ParticleType(const std::string& Name,
                           const ofColor& Color)
   : mName(Name)
   , mColor(Color)
   {

   }

const ofColor& ParticleType::Color() const
   {
   return mColor;
   }

const std::string& ParticleType::Name() const
   {
   return mName;
   }

float ParticleType::InteractionForce(const ParticleType& other) const
   {
   const auto it = mParticleInteractionMap.find(other.Name());
   if (it == mParticleInteractionMap.end())
      return 0.0f;

   return it->second;
   }

void ParticleType::SetInteractionForce(const ParticleType& other,
                                       const float Force)
   {
   constexpr float NeutralInteractionThreshold = 0.0001f;
   if (Force > -NeutralInteractionThreshold &&
      Force < NeutralInteractionThreshold)
      {
      mParticleInteractionMap[other.Name()] = 0.0f;
      return;
      }

   mParticleInteractionMap[other.Name()] = Force;
   }

std::map<std::string, float> ParticleType::ParticleInteractionMap() const
   {
   return mParticleInteractionMap;
   }
