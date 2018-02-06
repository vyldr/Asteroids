// Based on the rifle from skeet

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <cassert>
#include "point.h"
#include "uiDraw.h"
#include "velocity.h"

class Spaceship
{
public:
   Spaceship() : angle(270), vel(), starVel(), dead(false), super(false) { starVel.setWrap(false); } 
   void     move(int left, int right, int up);        // move the spaceship left or right or accelerate
   void     draw()         const;              // draw the spaceship at the current angle and position
   int      getAngle()     const { return angle;               }
   Velocity getVelocity()  const { return vel;                 }
   Point    getPoint()     const { return vel.getPoint();      }
   Point    getStarPoint() const { return starVel.getPoint();  }
   void     advance();
   bool     isDead()       const { return dead;                }
   void     setDead()            { dead = true;                }
   bool     isSuper()      const { return super;               }
   void     setSuper()           { super = true;               }
   
private:
   int angle;                         
   Velocity vel;
   Velocity starVel;
   bool dead;
   int super;
};

#endif // SPACESHIP_H
