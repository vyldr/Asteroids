#ifndef MEDIUM_H
#define MEDIUM_H

#include "asteroid.h"
#include "uiDraw.h"
#include "velocity.h"

class Medium : public Asteroid
{
   public:
      Medium(Velocity vel) : Asteroid(vel) { setScore(50); }
      void draw() const { drawPolygon(getVelocity().getPoint(), 15, 4, getAngle()); }      
};

#endif // MEDIUM_H
