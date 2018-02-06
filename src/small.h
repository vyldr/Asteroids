#ifndef SMALL_H
#define SMALL_H

#include "asteroid.h"
#include "uiDraw.h"
#include "velocity.h"

class Small : public Asteroid
{
   public:
      Small(Velocity vel) : Asteroid(vel) { setScore(100); }
      void draw() const { drawPolygon(getVelocity().getPoint(), 10, 3, getAngle()); }      
};

#endif // SMALL_H
