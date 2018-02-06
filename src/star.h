#pragma once
#include"velocity.h"
#include "uiDraw.h"

class Star
{
   private:
      Point pt;
      float depth;
      
   public:
      Star() : pt(random(pt.getXMin(), pt.getXMax()), random(-400.0, 400.0)), depth(random(-4.0, 1.5)) 
      { 
         if (depth < 0)
            depth = random(0.0, 1.0);
      };
      ~Star() {};
      void draw(Point spaceshipPt) const
      {
         Point drawPt;
         drawPt.setWrap(true);
         drawPt.setX(-(spaceshipPt.getX() * depth) + pt.getX());
         drawPt.setY(-(spaceshipPt.getY() * depth) + pt.getY());
         drawDot(drawPt, depth, 0);
      }
   
};
