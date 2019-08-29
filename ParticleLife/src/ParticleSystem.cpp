// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ParticleSystem.h"

#include <random>

ParticleSystem::ParticleSystem()
   : mFriction(0.01f)
   , mMinParticleInteractionDistSquared(30.0f * 30.0f)
   , mMaxParticleInteractionDistSquared(100.0f * 100.0f)
   , mParticleInitialMaxSpeed(0.05f)
   , mParticleRadius(10.0f)
   , mWindowHeight(ofGetWindowHeight())
   , mWindowWidth(ofGetWindowWidth())
   {

   }

bool ParticleSystem::CreateParticle(const std::string& ParticleTypeName,
                                    const int          Nb /* = 1 */)
   {
   const auto particleTypeIt = mParticleTypesMap.find(ParticleTypeName);
   if (particleTypeIt == mParticleTypesMap.end() || Nb <= 0)
      return (false);

   std::random_device rd;
   std::mt19937 RandomEngine(rd());

   std::uniform_real_distribution<float> randomPosX(0.0f, mWindowWidth);
   std::uniform_real_distribution<float> randomPosY(0.0f, mWindowHeight);
   std::uniform_real_distribution<float> randomSpeed(-mParticleInitialMaxSpeed, mParticleInitialMaxSpeed);

   for (int i = 0; i < Nb; ++i)
      {
      mParticles.emplace_back(particleTypeIt->second,
                              randomPosX(RandomEngine),
                              randomPosY(RandomEngine),
                              randomSpeed(RandomEngine),
                              randomSpeed(RandomEngine));
      }

   return (true);
   }

bool ParticleSystem::CreateParticleType(const std::string& Name,
                                        const ofColor&     Color)
   {
                             // Validate params
   if (Name.empty())
      return (false);

                             // Validate key unicity
   if (mParticleTypesMap.find(Name) != mParticleTypesMap.end())
      return (false);

   mParticleTypesMap.insert(std::make_pair(Name,
                                           ParticleType(Name,
                                                        Color)));

   return (true);
   }

float ParticleSystem::InteractForce(const std::string& ParticleTypeName,
                                    const std::string& OtherParticleTypeName) const
   {
   const auto particleIt = mParticleTypesMap.find(ParticleTypeName);
   const auto otherParticleIt = mParticleTypesMap.find(OtherParticleTypeName);
   if (particleIt == mParticleTypesMap.end() || otherParticleIt == mParticleTypesMap.end())
      return (0.0f);

   return (particleIt->second.InteractionForce(otherParticleIt->second)); 
   }

std::vector<ParticleType*> ParticleSystem::ParticleTypes()
   {
   std::vector<ParticleType*> particleTypes;
   for (auto& it : mParticleTypesMap)
      particleTypes.push_back(&(it.second));

   return (particleTypes);
   }

void ParticleSystem::Render() const
   {
   for (const Particle& particle : mParticles)
      {
      ofSetColor(particle.Color());
      ofDrawCircle(particle.PosX(), particle.PosY(), mParticleRadius);

                             // Smooth edge draw
      if (particle.PosX() - mParticleRadius < 0.0f)
         ofDrawCircle(mWindowWidth + particle.PosX(), particle.PosY(), mParticleRadius);
      else if (particle.PosX() + mParticleRadius > mWindowWidth)
         ofDrawCircle(particle.PosX() - mWindowWidth, particle.PosY(), mParticleRadius);

      if (particle.PosY() - mParticleRadius < 0.0f)
         ofDrawCircle(particle.PosX(), mWindowHeight + particle.PosY(), mParticleRadius);
      else if (particle.PosY() + mParticleRadius > mWindowHeight)
         ofDrawCircle(particle.PosX(), particle.PosY() - mWindowHeight, mParticleRadius);
      }
   }

bool ParticleSystem::SetInteractForce(const std::string& ParticleTypeName,
                                      const std::string& OtherParticleTypeName,
                                      const float        Force)
   {
   const auto particleTypeIt = mParticleTypesMap.find(ParticleTypeName);
   const auto otherParticleTypeIt = mParticleTypesMap.find(OtherParticleTypeName);
   if (particleTypeIt == mParticleTypesMap.end() || otherParticleTypeIt == mParticleTypesMap.end())
      return (false);

   particleTypeIt->second.SetInteractionForce(otherParticleTypeIt->second, Force);
   return (true);
   }

void ParticleSystem::Update()
   {
   UpdateParticlesSpeed();
   UpdateParticlesPosition();
   }

void ParticleSystem::UpdateParticlesPosition()
   {
   for (Particle& particle : mParticles)
      {
      particle.SetPosX(particle.PosX() + particle.SpeedX());
      particle.SetPosY(particle.PosY() + particle.SpeedY());

      if (particle.PosX() < 0.0f)
         particle.SetPosX(particle.PosX() + mWindowWidth);
      else if (particle.PosX() > mWindowWidth)
         particle.SetPosX(particle.PosX() - mWindowWidth);

      if (particle.PosY() < 0.0f)
         particle.SetPosY(particle.PosY() + mWindowHeight);
      else if (particle.PosY() > mWindowHeight)
         particle.SetPosY(particle.PosY() - mWindowHeight);

                             // Apply friction
      particle.SetSpeedX(particle.SpeedX() * (1.0f - mFriction));
      particle.SetSpeedY(particle.SpeedY() * (1.0f - mFriction));
      }
   }

void ParticleSystem::UpdateParticlesSpeed()
   {
   const float minParticleInteractionDist = std::sqrtf(mMinParticleInteractionDistSquared);

   for (Particle& particle : mParticles)
      {
      for (const Particle& otherParticle : mParticles)
         {
                             // Ignore current particle
         if (&particle == &otherParticle)
            continue;

         float dx = otherParticle.PosX() - particle.PosX();
         float dy = otherParticle.PosY() - particle.PosY();

         if (dx > mWindowWidth * 0.5f)
            dx -= mWindowWidth;
         else if (dx < mWindowWidth * -0.5f)
            dx += mWindowWidth;

         if (dy > mWindowHeight * 0.5f)
            dy -= mWindowHeight;
         else if (dy < mWindowHeight * -0.5f)
            dy += mWindowHeight;

         const float distanceSquared = dx * dx + dy * dy;
         if (distanceSquared > mMaxParticleInteractionDistSquared)
            continue;

         const float distance = std::sqrt(distanceSquared);

         const float dxn = dx / distance;
         const float dyn = dy / distance;

         float interactForce = InteractForce(particle.Type().Name(),
                                             otherParticle.Type().Name());

                             // Separation force
         if (distance < minParticleInteractionDist)
            interactForce = 2.0f * minParticleInteractionDist * (1.0f / (minParticleInteractionDist + 2.0f) - 1.0f / (distance + 2.0f));

         particle.SetSpeedX(particle.SpeedX() + interactForce * dxn);
         particle.SetSpeedY(particle.SpeedY() + interactForce * dyn);
         }
      }
   }
