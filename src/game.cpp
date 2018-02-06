/***********************************************************************
 * Author:
 *    Steven Wilde
 * Summary:
 *    This is the classic Asteroids game
 ************************************************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "large.h"
#include "medium.h"
#include "small.h"
#include "super.h"
#include "star.h"
#include "saucer.h"
#include <vector>
#include <list>
#include <cmath>

using namespace std;

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : gameOver(false), score(0), scorePt(-290, 290)
   { 
      for (int i = 0; i < 4; i++)
      {
         if (!i)
            large.push_back(Large(true));
         else
            large.push_back(Large(false)); 
      }
   }
   
   // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw(const Interface & ui);
   
private:
   // Create ship, bullets and rocks
   vector<Bullet> bullets;
   vector<Large> large;
   vector<Medium> medium;
   vector<Small> small;
   vector<Super> super;
   Star stars[1000];

   bool gameOver;
   
   Spaceship spaceship;
   Saucer saucer;

   // add any objects or variables that are required

   int score;
   Point scorePt;

   void detectHits();
   void removeDeadObjects();

};

/***************************************
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // Advance anything that moves
   
   // spaceship
   if (!gameOver)
      spaceship.advance();
      
   // saucer
   if (!saucer.isDead())
      saucer.advance();
   
   // bullets
   for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
   {
      it->advance();
   }
   
   // rocks
   for (vector<Large>::iterator it = large.begin(); it != large.end(); ++it)
      it->advance();
   for (vector<Medium>::iterator it = medium.begin(); it != medium.end(); ++it)
      it->advance();
   for (vector<Small>::iterator it = small.begin(); it != small.end(); ++it)
      it->advance();
   for (vector<Super>::iterator it = super.begin(); it != super.end(); ++it)
      it->advance();
   
   // saucer firing
   if ((random(0, 100) == 0) and (!saucer.isDead()) and !gameOver)
      bullets.push_back(Bullet(spaceship.getVelocity(), saucer.getVelocity()));
   

   // Decide if anything died, the game is over, etc...
   detectHits();
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // fire
   if (ui.isSpace() and !gameOver)
   {
      // create a bullet and add it to the vector
      Velocity tvel;
      tvel.setVelocity(spaceship.getAngle(), 5);
      bullets.push_back(Bullet(spaceship.getVelocity() + tvel));
   }

  if (bullets.size() > 0)
  {
    // Notice that the For loop doesn't increment "it" in the normal place 
    for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
    {
      if (it->getTime() > 100)
      {
	      // When you delete a point, don't move the iterator
	      it = bullets.erase(it);
      }
      else
      {
        // Move to the next point in the vector
        ++it;
      }
    }
  }
  
  spaceship.move(ui.isLeft(), ui.isRight(), ui.isUp());
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   // Draw anything you need to display in the game
   for (int i = 0; i < 1000; i++)
      stars[i].draw(spaceship.getStarPoint());

   if (!gameOver)
      spaceship.draw();
      
   if (!saucer.isDead())
      saucer.draw();

   drawNumber(scorePt, score);

   // draw all of the bullets
   for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
      it->draw();
  
  
   // draw the asteroids
   for (vector<Large>::iterator it = large.begin(); it != large.end(); ++it)
      it->draw();
   for (vector<Medium>::iterator it = medium.begin(); it != medium.end(); ++it)
      it->draw();
   for (vector<Small>::iterator it = small.begin(); it != small.end(); ++it)
      it->draw();
   for (vector<Super>::iterator it = super.begin(); it != super.end(); ++it)
      it->draw();
}

/*********************************************
 * GAME :: detectHits
 * Detect any rocks hitting bullets and ship and make them "dead"
 * Note: decide if the game is over here
 *********************************************/
void Game::detectHits()
{
  // did any bullets hit a rock?
   for (vector<Large>::iterator rock = large.begin(); rock != large.end(); ++rock)
   {
      for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
         if ((rock->getVelocity() - it->getVelocity()) < 20 and !it->isDead())
         {
            it->setDead();
            Velocity tvel;
            tvel.setDy(1);
            rock->setDead();
            score += rock->getScore();
            medium.push_back(Medium(rock->getVelocity() + tvel)); 
            tvel.setDy(-1);
            medium.push_back(Medium(rock->getVelocity() + tvel)); 
            tvel.setDy(0);
            tvel.setDx(2);
            small.push_back(Small(rock->getVelocity() + tvel)); 
            tvel.setDx(random(-3, 3));
            tvel.setDy(random(-3, 3));
            if (rock->isSuper())
               super.push_back(Super(rock->getVelocity() + tvel));
         }
      if (((rock->getVelocity() - spaceship.getVelocity()) < 30) and !gameOver)
      {
         if (!spaceship.isSuper())
            gameOver = true;
         rock->setDead();
      }
   }

   for (vector<Medium>::iterator rock = medium.begin(); rock != medium.end(); ++rock)
   {
      for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
         if ((rock->getVelocity() - it->getVelocity()) < 15 and !it->isDead())
         {
            it->setDead();
            rock->setDead();
            score += rock->getScore();
            Velocity tvel;
            tvel.setDx(3);
            small.push_back(Small(rock->getVelocity() + tvel)); 
            tvel.setDx(-3);
            small.push_back(Small(rock->getVelocity() + tvel)); 
         }
      if (((rock->getVelocity() - spaceship.getVelocity()) < 20) and !gameOver)
      {
         if (!spaceship.isSuper())
            gameOver = true;
         rock->setDead();
      }
   }

   for (vector<Small>::iterator rock = small.begin(); rock != small.end(); ++rock)
   {
      for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
         if ((rock->getVelocity() - it->getVelocity()) < 10 and !it->isDead())
         {
            it->setDead();
            rock->setDead();
            score += rock->getScore();
         }
      if (((rock->getVelocity() - spaceship.getVelocity()) < 15) and !gameOver)
      {
         if (!spaceship.isSuper())
            gameOver = true;
         rock->setDead();
      }
   }

   for (vector<Super>::iterator rock = super.begin(); rock != super.end(); ++rock)
   {
      for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
         if ((rock->getVelocity() - it->getVelocity()) < 20 and !it->isDead())
         {
            it->setDead();
            rock->setDead();
            score += rock->getScore();
         }
      if (((rock->getVelocity() - spaceship.getVelocity()) < 25) and !gameOver)
      {
         rock->setDead();
         spaceship.setSuper();
      }
   }
   
   
   for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
      if ((saucer.getVelocity() - it->getVelocity()) < 10 and !it->isDead() and !saucer.isDead() and it->isEnemy())
      {
         saucer.setDead();
         it->setDead();
      }

   for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
      if ((spaceship.getVelocity() - it->getVelocity()) < 10 and !it->isDead() and !it->isEnemy() and !spaceship.isSuper())
      {
         gameOver = true;
         it->setDead();
      }
  // remove the dead
  removeDeadObjects();
}

/*********************************************
 * GAME :: removeDeadObjects
 * remove any "dead" rocks, bullets, etc...
 *********************************************/
void Game::removeDeadObjects()
{
   for (vector<Large>::iterator rock = large.begin(); rock != large.end();)
      if (rock->isDead())
         rock = large.erase(rock);
      else 
         rock++;

   for (vector<Medium>::iterator rock = medium.begin(); rock != medium.end();)
      if (rock->isDead())
         rock = medium.erase(rock);
      else 
         rock++;
   
   for (vector<Small>::iterator rock = small.begin(); rock != small.end();)
      if (rock->isDead())
         rock = small.erase(rock);
      else 
         rock++;
   
   for (vector<Super>::iterator rock = super.begin(); rock != super.end();)
      if (rock->isDead())
      {
         rock = super.erase(rock);
      }
      else 
         rock++;
         
   for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
      if (it->isDead())
         it = bullets.erase(it);
      else
         it++;
}

#define X_SIZE       600

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;

   pGame->advance();
   pGame->input(*pUI);
   pGame->draw(*pUI);
}

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -300.0;
float Point::yMax =  300.0;

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Asteroids");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
