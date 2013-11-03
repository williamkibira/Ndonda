/*
    Copyright (c) 2013, <copyright holder> <email>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <SDL2/SDL.h>
#include "../Tools/bodyconstructor.h"
#include "../Tools/debugdraw.h"
#include "../Tools/collisiondetection.h"
#include "../Views/camera.h"
//#include "textrenderer.h"
#include "../Tests/Theo/theojansen.h"
#include "../Tests/Car/car.h"
#ifndef MOBILESIMULATOR_H
#define MOBILESIMULATOR_H

class MobileSimulator
{

public:
  MobileSimulator(b2World* world);
  bool engageSimulator();
  void simulationLoop();
  bool initSDL();
  bool initOpenGL();
  void update_viewport();
  void getDisplayMode();
    virtual ~MobileSimulator();
private:
  CollisionDetection* collisioncheck;
  DebugDraw debugdraw;
  bool running;
  b2World* world;
  int SCREEN_HEIGHT;
  int SCREEN_WIDTH;
  int BPP;
  int LEVEL_HEIGHT;
  int LEVEL_WIDTH;
  Camera* camera;
  std::string screentext;
  SDL_GLContext glcontext;
  SDL_Renderer* gRenderer;
  SDL_Window* window;
  SDL_Event event;
  //TextRenderer* text_show;
  
  // Our test Subject Theo jansen
  TheoJansen* theo;
  Car* car;
  
  float timeStep;
  int velocityIterations ;
  int  positionIterations ;
};

#endif // MOBILESIMULATOR_H
