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


#include "groundbody.h"

GroundBody::GroundBody(b2World* world, float positionX,float positionY,const Tmx::Polyline* polyline,ConvertUtililty* convert):Body(world,positionX,positionY)
{
  this->convert = convert;
  density = 1;
  friction = 0.3;
  int count = 0;
  b2Vec2* vertices = new b2Vec2[polyline->GetNumPoints()];
  for(int i = 0; i < polyline->GetNumPoints(); ++i)
  {   const Tmx::Point point = polyline->GetPoint(i);
      //vertices[i].Set(point.x/PIXEL_TO_METER, point.y/PIXEL_TO_METER);
      vertices[i]= convert->convertPixelsToPoints(point.x,point.y);
      count++;
  }
  chain.CreateChain(vertices,count);
}
void GroundBody::drawPoint(float pos_x, float pos_y)
{
      glVertex2f(pos_x,pos_y);
}
void GroundBody::engageGround()
{
 bodyDef.type = b2_staticBody;
 bodyDef.position = position;
 fixtureDef.shape = &chain;
 fixtureDef.density = density;
 fixtureDef.friction = friction;
 body = world->CreateBody(&bodyDef);
 body->CreateFixture(&fixtureDef);
}
b2Vec2 GroundBody::getBodyPosition()
{
  return body->GetPosition();
}
GroundBody* GroundBody::returnBody()
{
 return this;
}
void GroundBody::getUserData(void* userdata)
{
  body->SetUserData(userdata);
}
void GroundBody::setBodyPosition(float positionX, float positionY)
{
// position.x = positionX;
// position.y = positionY;
   position = convert->convertObjectPointToGamePoint(positionX,positionY);
}
void GroundBody::setDensity(float density)
{
 this->density = density;
}
void GroundBody::setFriction(float friction)
{
 this->friction = friction;
}
void GroundBody::Update()
{
  GM_POINT* pos = convert->convertB2Vec2ToGM_Point(body->GetPosition());
      printf("TRANSLATED OVER TO :X[%4.2f] :Y[%4.2f]\n",pos->x,pos->y);
     glTranslatef(pos->x,pos->y,0.0f);
   glBegin(GL_POLYGON);
   glColor3f(0.0,1.0,0.0);
   
   for(int i =0; i < chain.m_count; ++i)
   { 
       GM_POINT* pos_1 = convert->convertB2Vec2ToGM_Point(chain.m_vertices[i]);
       printf("Body Draw Points : X[%4.2f]--Y[%4.2f]\n",pos_1->x,pos_1->y);
       drawPoint(pos_1->x,pos_1->y); 
      
   }
   glEnd();
}




GroundBody::~GroundBody()
{

}

