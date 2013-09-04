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


#include "ground.h"

Ground::Ground(b2World* world,float width,float height)
{
this->width = width;
this->height = height;
this->world = world;
 convert = new ConvertUtililty(0,0);
 
 //groundBodyDef.type = b2_staticBody;
 groundBodyDef.position.Set(30.0f,10.0f);

        // Call the body factory which allocates memory for the ground body
        // from a pool and creates the ground box shape (also from a pool).
        // The body is also added to the world.
 groundBody = world->CreateBody(&groundBodyDef);

        // Define the ground box shape.
        

        // The extents are the half-widths of the box.
 groundBox.SetAsBox(width, height);

        // Add the ground fixture to the ground body.
 groundBody->CreateFixture(&groundBox, 0.0f);

}
b2Vec2 Ground::getGroundPosition()
{
 return groundBody->GetPosition();
}

void Ground::DrawGround()
{
  
  GM_POINT* Gpoint = convert->convertB2Vec2ToGM_Point(groundBody->GetPosition()); 
 glLoadIdentity();
 glPushMatrix();
 glTranslatef(Gpoint->x,Gpoint->y,0.0f);
 glRotatef(convert->convertRadiansToDegrees(groundBody->GetAngle()),0.0f,0.0f,1.0f);
 glBegin(GL_POLYGON);
       glColor3f(1.0,0.0,0.0); glVertex2f(-width*PIXEL_TO_METER,height*PIXEL_TO_METER);
       glColor3f(0.0,1.0,0.0); glVertex2f(width*PIXEL_TO_METER,height*PIXEL_TO_METER);
       glColor3f(0.0,0.0,1.0); glVertex2f(width*PIXEL_TO_METER,-height*PIXEL_TO_METER);
       glColor3f(0.0,0.0,1.0); glVertex2f(-width*PIXEL_TO_METER,-height*PIXEL_TO_METER);
 glEnd();
 glPopMatrix();
}
float Ground::getAngle()
{
 return groundBody->GetAngle();
}

Ground::~Ground()
{

}

