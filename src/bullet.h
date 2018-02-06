#ifndef BULLET_H
#define BULLET_H

#include "velocity.h"
#include "uiDraw.h"


class Bullet
{
   public:
      // Your bullets
      Bullet(Velocity tvel) : vel(tvel), time(0), dead(false), enemy(true), type(1) { }   
      
      // The saucer's bullets
      Bullet(Velocity spaceship, Velocity saucer) : vel(saucer.getX(), saucer.getY(), 
         (saucer.getX() - spaceship.getX()), (spaceship.getY() - saucer.getY())), time(0), 
         dead(false), enemy(false), type(-1) { vel.setMag(5); }
      
      void     advance()            { vel++; time++;                       }
      void     draw()         const { drawDot(vel.getPoint(), 2.0, type);  }
      float    getX()         const { return vel.getX();                   }
      float    getY()         const { return vel.getY();                   }
      Velocity getVelocity()  const { return vel;                          }
      bool     isDead()       const { return dead;                         }
      void     setDead()            { dead = true;                         }
      Point    getPoint()           { return vel.getPoint();               } 
      int      getTime()      const { return time;                         }
      bool     isEnemy()      const { return enemy;                        }
      
   private:
      Velocity vel;
      bool dead;
      int time;
      bool enemy;
      int type;
};

#endif // BULLET_H

