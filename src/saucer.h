#ifndef SAUCER_H
#define SAUCER_H

#include "point.h"
#include "uiDraw.h"
#include "velocity.h"

class Saucer
{
   public:
      Saucer() : vel(0, -200, 0, 0), dead(false) {} 

      void     draw()         const { drawSaucer(vel.getPoint()); } 
      Velocity getVelocity()  const { return vel;                 }
      Point    getPoint()     const { return vel.getPoint();      }
      void     advance()            
      { 
         vel.setDx((vel.getDx() + random(-1.5, 1.5)) * 0.99); 
         vel.setDy((vel.getDy() + random(-1.5, 1.5)) * 0.99); 
         vel++; 
      }
      bool     isDead()       const { return dead;    }
      void     setDead()            { dead = true;    }
   private:
      Velocity vel;
      bool dead;   
};


#endif // SAUCER_H
