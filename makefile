###############################################################
# Program:
#     Project 4, Asteroids
#     Brother Comeau, CS165
# Author:
#     Steven Wilde
# Summary:
#     This program is the game Asteroids.  You control a spaceship 
#     and shoot at asteroids while avoiding the asteroids.  I added
#     some extra features to the game: 
#        - One of the asteroids contains a star that you can shoot 
#          for points or grab for temporary invulnerability.  While 
#          you are invulnerable, the spaceship flashes different colors.  
#        - Your score is displayed at the top left corner.  
#        - The background has stars that move based on how the spaceship 
#          moves.  
#        - There is a saucer that flies around and shoots at you.  
#        - your bullets are red and the saucer's bullets are green.  
###############################################################

# for the linux VM in vmware, you need to add '-lGL' to LFLAGS
LFLAGS = -lGL -lglut -lGLU

# vars for the backup feature
PACKAGE   = backup
VERSION   = ` date +"%Y%m%d_%H%M%S" `
ARCHIVE   = $(PACKAGE)-$(VERSION)

bin/asteroids: build/game.o build/uiInteract.o build/uiDraw.o build/point.o build/velocity.o build/spaceship.o
	g++ -o bin/asteroids build/*.o $(LFLAGS)

###############################################################
# Individual files
#    game.o        The Asteroids game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    velocity.o    velocity class
#    point.o       Point class
#    spaceship.o   Spaceship class
###############################################################
build/game.o: src/game.cpp src/uiDraw.h src/uiInteract.h src/point.h src/spaceship.h src/bullet.h src/large.h src/medium.h src/small.h src/super.h src/star.h src/saucer.h
	g++ -c src/game.cpp -o build/game.o

build/uiInteract.o: src/uiInteract.cpp src/uiInteract.h
	g++ -c src/uiInteract.cpp -o build/uiInteract.o

build/uiDraw.o: src/uiDraw.cpp src/uiDraw.h
	g++ -c src/uiDraw.cpp -o build/uiDraw.o

build/velocity.o: src/velocity.cpp src/velocity.h src/point.h
	g++ -c src/velocity.cpp -o build/velocity.o

build/point.o: src/point.cpp src/point.h
	g++ -c src/point.cpp -o build/point.o

build/spaceship.o: src/spaceship.cpp src/spaceship.h src/point.h src/uiDraw.h src/velocity.h
	g++ -c src/spaceship.cpp -o build/spaceship.o

###############################################################
# General rules
###############################################################
clean:
	rm build/* bin/asteroids

again:
	make clean; make

all:
	make clean; make && make go

go:
	bin/asteroids