#include "spaceship.h"

/*****************************************
 * SPACESHIP : DRAW
 * Draw the spaceship
 *****************************************/
void Spaceship::draw() const
{
   // make the point static so we don't have to chagne it.
   static const Point point;
   Point corner(point.getXMax() + 1, point.getYMin());
   
   drawShip(vel.getPoint(), angle, super);
}

/*******************************************
 * SPACESHIP : MOVE
 * Move the spaceship up or down or accelerate
 *****************************************/
void Spaceship::move(int left, int right, int up)
{
   // make sure we get rational data from the caller
   assert(left >= 0 && right >= 0 && up >= 0);
   
   // adjust the spaceship
   if (left)
      angle += 10;
   if (right)
      angle -= 10;
   if (up)
   {
      Velocity tvel;
      tvel.setVelocity(angle, 0.2);
      vel += tvel;
   }
}

/*******************************************
 * SPACESHIP : ADVANCE
 * advance the spaceship
 ******************************************/
void Spaceship::advance()
{
   vel.addX(vel.getDx());
   vel.addY(vel.getDy());
   starVel.addX(vel.getDx());
   starVel.addY(vel.getDy());

   // Invulnerability is temporary
   if (super)
      super++;
   if(super >= 300)
      super = 0;
   
}
