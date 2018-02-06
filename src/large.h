#ifndef LARGE_H
#define LARGE_H

#include "asteroid.h"
#include "uiDraw.h"
#include "velocity.h"

class Large : public Asteroid
{
   public:
      Large(bool tsuper) : Asteroid(), super(tsuper) { setScore(20); }
      void draw() const { drawPolygon(getVelocity().getPoint(), 20, 5, getAngle()); }     
      bool isSuper() const { return super; }
   private:
      bool super; 
};

#endif // LARGE_H
