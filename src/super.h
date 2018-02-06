#ifndef SUPER_H
#define SUPER_H

#include "asteroid.h"
#include "uiDraw.h"
#include "velocity.h"

class Super : public Asteroid
{
   public:
      Super(Velocity vel) : Asteroid(vel) { setScore(20); }
      Super() : Asteroid() { setScore(12); }
      void draw() const { drawStar(getVelocity().getPoint(), 10, getAngle()); }      
};

#endif // SUPER_H
