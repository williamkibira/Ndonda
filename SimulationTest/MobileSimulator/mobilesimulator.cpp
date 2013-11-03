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


#include "mobilesimulator.h"

MobileSimulator::MobileSimulator(b2World* world)
{
  this->world = world;
  this->BPP = 32;
  getDisplayMode();
  camera = new Camera(SCREEN_HEIGHT,SCREEN_WIDTH);
  //text_show = new TextRenderer(SCREEN_HEIGHT,SCREEN_WIDTH,gRenderer);
}
void MobileSimulator::getDisplayMode()
{
  int screen = 0;
  int modes = SDL_GetNumDisplayModes(screen);
  for(int i = 0; i < modes; ++i){
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(screen,i,&mode);
    
    if(SCREEN_WIDTH < mode.w){
      SCREEN_WIDTH =  mode.w;
      SCREEN_HEIGHT = mode.h;  
    }
  }
}

bool MobileSimulator::engageSimulator()
{
  timeStep = 1.0f / 60.0f;
  velocityIterations = 6;
  positionIterations = 1;
  
  collisioncheck = new CollisionDetection();
  
  world->SetDebugDraw(&debugdraw);
  
  world->SetContactListener(collisioncheck); // Collision Check Simulation
  
  // Load The subject to test
  theo = new  TheoJansen(world);
  // car = new Car(world);
}
bool MobileSimulator::initOpenGL()
{
  glEnable(GL_TEXTURE_2D); 
  glEnable(GL_BLEND); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
  glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f,SCREEN_WIDTH,0.0f,SCREEN_HEIGHT,-100.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}
bool MobileSimulator::initSDL()
{
  if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
  {
    printf("FAILED TO INIT VIDEO MODE\n");
    exit(0);
  }
  
  
  // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
  //SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
  window = SDL_CreateWindow(
    "Simulator Trial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
  
  // Create an OpenGL context associated with the window.
  glcontext = SDL_GL_CreateContext(window);  
  gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  if(gRenderer == NULL){
    printf("FAILED TO CREATE THE WINDOW \n");
    exit(0);
  }
}
void MobileSimulator::update_viewport()
{
  int temp = SCREEN_HEIGHT;
  SCREEN_HEIGHT = SCREEN_WIDTH;
  SCREEN_WIDTH = temp;
  glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f,SCREEN_WIDTH,0.0f,SCREEN_HEIGHT,-100.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void MobileSimulator::simulationLoop()
{
  running = true;
  while(running){
    
    glClearColor ( 0.0, 0.0, 0.0, 0.0 );
    glClear(GL_COLOR_BUFFER_BIT); // clearing screen
    
    while(SDL_PollEvent(&event)!= 0){  // Check for events.
	   {
	     if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
	       running = false;
	     }else if(event.type == SDL_KEYDOWN){
	       
	       theo->move(event.key.keysym.sym);
	       //car->move(event.key.keysym.sym);
	     }else{
	       if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED){
		 update_viewport();
	      }
	    }
	   }
	   
    }
    
    //camera->setCameraPosition(car->getPosition(),car->getAngle());
    camera->setCameraPosition(theo->getPosition(),theo->getAngle());  
    debugdraw.SetFlags(b2Draw::e_shapeBit /*+b2Draw::e_aabbBit*/+ b2Draw::e_jointBit + b2Draw::e_pairBit + b2Draw::e_centerOfMassBit);
    world->DrawDebugData();
    world->SetWarmStarting(true);
    world->SetContinuousPhysics(true); 
    world->Step(timeStep, velocityIterations, positionIterations);
    //text_show->showText("ACTIVE");
    SDL_RenderPresent( gRenderer );
    SDL_GL_SwapWindow(window);  // Swap the window/buffer to display the result 
    
    
  }
  SDL_GL_DeleteContext(glcontext);   
  // Done! Close the window, clean-up and exit the program. 
  SDL_DestroyWindow(window);
  SDL_Quit();
}

MobileSimulator::~MobileSimulator()
{

}

