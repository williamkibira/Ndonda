#include <iostream>
#include <Box2D/Box2D.h>
#include "Simulator/simulator.h"
int main(int argc, char **argv) {
  
  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);
   Simulator* sim = new Simulator(&world);
   sim->initOpenGL();
   sim->initSDL();
   sim->engageSimulator();
   sim->simulationLoop();
    return 0;
}
