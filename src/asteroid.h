#ifndef ASTEROID_H
#define ASTEROID_H

#include "uiDraw.h"
#include "velocity.h"

/**********************************
 * Base class for asteroids
 **********************************/
 
class Asteroid
{
   public:
      // Create large asteroid
      Asteroid() : vel((random(100, 300) * (random(0, 2) * 2 - 1)), (random(100, 300) * (random(0, 2) * 2 - 1)), 
         random(-3.0, 3.0), random(-3.0, 3.0)), angle(random(0, 72)), 
         rotation(random(-6.0, 6.0)), dead(false) {  }
      
      // create asteroid when another is destroyed
      Asteroid(Velocity tvel) : vel(tvel), angle(random(0, 72)), 
         rotation(random(-6.0, 6.0)), dead(false) {  }
         
      virtual void draw() const = 0;
      virtual void advance()           { vel++; angle += rotation; }
      Velocity getVelocity()     const { return vel;               }
      int   isDead()             const { return dead;              }
      void  setDead()                  { dead = true;              }
      int   getScore()           const { return score;             }
      void  setScore(int number)       { score = number;           }
      float getX()               const { return vel.getX();        }
      float getY()               const { return vel.getY();        }
      float getDx()              const { return vel.getDx();       }
      float getDy()              const { return vel.getDy();       }
      int   getAngle()           const { return angle;             }
   private:
      Velocity vel;
      bool dead;
      int score;
      int angle;
      int rotation;
};

#endif // ASTEROID_H
