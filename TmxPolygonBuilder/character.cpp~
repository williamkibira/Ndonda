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


#include "character.h"

Character::Character(b2World* world,float width,float height)
{
  
 convert = new  ConvertUtililty(0,0);
 audiomgr = new AudioManager();
 audiomgr->setVolumeLevel(1.0);
 
this->height = height;
this->width = width;
this->world = world;
Shape.SetAsBox(width,height);
input = new Input();

bodyDef.position.Set(30.0f,50.0f);
bodyDef.type = b2_dynamicBody;
fixtureDef.shape = &Shape;
fixtureDef.density = 1.0f;
fixtureDef.friction = 0.3f;

body = world->CreateBody(&bodyDef);
body->CreateFixture(&fixtureDef);
body->SetUserData(this);
}
b2Vec2 Character::getPosition()
{
  return body->GetPosition();
}

void Character::move (int key )
{       velocity = body->GetLinearVelocity();
         
        switch(key)
	{
	  case SDLK_UP:{
	   printf("UP IS PRESSED\n");
	   
           //float impulse = body->GetMass() * 40;
           //body->ApplyLinearImpulse( b2Vec2(0,impulse), body->GetWorldCenter() );
	    
	    audiomgr->playEffect("./sounds/thunder.wav"); 
            velocity.y = 10;//upwards - don't change x velocity
           
	  }
	  break;
	  case SDLK_DOWN:{
	    printf("DOWN IS PRESSED\n");
	    audiomgr->playEffect("./sounds/snapshot.wav");
	    velocity.x *=  0.98;
	    
	  }
	  break;
	  case SDLK_LEFT:{
	    printf("LEFT IS PRESSED\n");
	    audiomgr->playEffect("./sounds/maxuh.wav");
	    velocity.x = b2Max( velocity.x - 0.1f, -5.0f );
	    
	  }
	  break;
	  case SDLK_RIGHT:{
	    printf("RIGHT IS PRESSED\n");
	    audiomgr->playEffect("./sounds/marytoss.wav");
	    velocity.x = b2Min( velocity.x + 0.1f,  5.0f );
	    
	  }
	    break;
	} 
	 body->SetLinearVelocity( velocity );
}
void Character::draw()
{   
     
     GM_POINT* Gpoint = convert->convertB2Vec2ToGM_Point(body->GetPosition());
     glLoadIdentity();
     glPushMatrix();
     glTranslatef(Gpoint->x,Gpoint->y,0.0f);
     glRotatef((float)convert->convertRadiansToDegrees(body->GetAngle()),0.0f,0.0f,1.0f);
     glBegin(GL_POLYGON);
     
       glColor3f(1.0,0.0,0.0); glVertex2f(-width*PIXEL_TO_METER,height*PIXEL_TO_METER);
       glColor3f(0.0,1.0,0.0); glVertex2f(width*PIXEL_TO_METER,height*PIXEL_TO_METER);
       glColor3f(0.0,0.0,1.0); glVertex2f(width*PIXEL_TO_METER,-height*PIXEL_TO_METER);
       glColor3f(0.0,0.0,1.0); glVertex2f(-width*PIXEL_TO_METER,-height*PIXEL_TO_METER);
     
     glEnd();
     glPopMatrix();
}

float Character::getAngle()
{
 return body->GetAngle();
}


Character::~Character()
{

}

