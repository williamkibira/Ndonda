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


#include "box.h"

Box::Box(b2World* world)
{
  this->world = world;
  box.SetAsBox(0.5f, 0.5f);
  bd.position = position;
  b2PolygonShape box;
  box.SetAsBox(0.5f, 0.5f);
  

 
  bd.type = b2_dynamicBody;
  
  bd.position.Set(230.0f, 0.5f);
  body = world->CreateBody(&bd);
  body->CreateFixture(&box, 0.5f);
  
  bd.position.Set(230.0f, 1.5f);
  body = world->CreateBody(&bd);
  body->CreateFixture(&box, 0.5f);
  
  bd.position.Set(230.0f, 2.5f);
  body = world->CreateBody(&bd);
  body->CreateFixture(&box, 0.5f);
  
  bd.position.Set(230.0f, 3.5f);
  body = world->CreateBody(&bd);
  body->CreateFixture(&box, 0.5f);
  
  bd.position.Set(230.0f, 4.5f);
  body = world->CreateBody(&bd);
  body->CreateFixture(&box, 0.5f);
  convert = new ConvertUtililty();
}
void Box::draw()
{ 
  GM_POINT* pos = convert->convertB2Vec2ToGM_Point(body->GetPosition());
 b2Fixture* fixture =  body->GetFixtureList();
  b2PolygonShape* polyshape = (b2PolygonShape*)fixture->GetShape();
  
  
  glTranslatef(pos->x,pos->y,0.0f);
  glRotatef(convert->convertRadiansToDegrees(body->GetAngle()),0.0f,0.0f,1.0f);
  glBegin(GL_POLYGON);
  for(int i = 0; i < polyshape->m_vertexCount;++i){
     
    GM_POINT* point = convert->convertB2Vec2ToGM_Point(polyshape->m_vertices[i]);
  glVertex2f(point->x,point->y);
  }
  glEnd();
}

Box::~Box()
{
  
}



