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


#include "simulator.h"


Simulator::Simulator(b2World* world,std::string filename)
{   this->world = world;
    //tmxLoader = new TmxBodyLoader(filename,this->world);
    SCREEN_WIDTH = 640;//tmxLoader->getScreenWidth();
    SCREEN_HEIGHT = 480;//tmxLoader->getScreenHeight();
    //dynaBody = tmxLoader->getDynamicBodies(); // grab dynamic bodies vector
    //statBody = tmxLoader->getStaticBodies(); // grab static bodies vector
    camera_0 = new Camera(SCREEN_HEIGHT,SCREEN_WIDTH);
    input = new Input();
    audiomgr = new AudioManager();
    audiomgr->loadsong("./sounds/wave2.mp3");
    audiomgr->setVolumeLevel(1.0);
}
void Simulator::initOpenGL()
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
void Simulator::initSDL()
{
        	if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
    	printf("FAILED TO INIT VIDEO MODE\n");
        exit(0);
    }
         printf("BEFORE CREATING WINDOW\n");
   
    // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
     window = SDL_CreateWindow(
"SDL2 Based Algorithm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
         printf("AFTER CREATING WINDOW\n");
// Create an OpenGL context associated with the window.
   glcontext = SDL_GL_CreateContext(window);  
}

void Simulator::initializeSimulator()
{
    // Create the ground bodies for the simulation
        character = new Character(world,1.0f,1.0f);
        ground = new Ground(world,50.0f,1.0f);
	
	 timeStep = 1.0f / 60.0f;
         velocityIterations = 6;
         positionIterations = 1;
	 audiomgr->playStream("./sounds/wave.mp3");
}
void Simulator::DrawObjects()
{
  glPushMatrix();
character->draw();
ground->DrawGround();
  glPopMatrix();
  glFlush();
}

void Simulator::simulatorLoop()
{        running = true;
         while(running){
	  
	         glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	         glClear(GL_COLOR_BUFFER_BIT); // clearing screen
		     
     while(SDL_PollEvent(&event)!= 0)  // Check for events.
	   {
        if(event.type == SDL_QUIT || event.type == SDL_QUIT){
            running = false;
	}
    else if(event.type == SDL_KEYDOWN)
		{
		  
		  character->move(event.key.keysym.sym);
		
		}
	   }
                 camera_0->setCharacterSize(4.5f,4.5f);
		 camera_0->setCameraPosition(character->getPosition(),character->getAngle());
		   
                   character->draw();
		   ground->DrawGround();
		  b2Vec2 pos= ground->getGroundPosition();
		  
		 
		  
	        // DrawObjects();
	       
                
                world->Step(timeStep, velocityIterations, positionIterations);
               
	       
	        
		SDL_GL_SwapWindow(window);  // Swap the window/buffer to display the result.
		//SDL_Delay(10);    
                audiomgr->update();
		
	 }
        
	SDL_GL_DeleteContext(glcontext);   
  // Done! Close the window, clean-up and exit the program. 
  SDL_DestroyWindow(window);
  SDL_Quit();
}


Simulator::~Simulator()
{

}