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


#include "staticbody.h"

StaticBody::StaticBody(b2World* world, float positionX,float positionY,const Tmx::Polygon* polygon,ConvertUtililty* convert):Body(world,positionX,positionY)
{  
  this->convert = convert;
  friction = 0.3;
  density = 1.0;
  bodyShape.m_vertexCount = polygon->GetNumPoints();
  
  for(int i = 0;  i < polygon->GetNumPoints(); ++i)
  {
    const Tmx::Point point = polygon->GetPoint(i);
    bodyShape.m_vertices[i] = convert->convertPixelsToPoints(point.x,point.y); 
  }
  
  CCWT();
}
void StaticBody::CCWT()
{
  
  NumberOfPolygonVertices = bodyShape.m_vertexCount;
  // We calculate the area of the polygon to see if their is any interscection
  
  // if area > we are in trouble
  area = 0;
  
  for (int i = 0; i < NumberOfPolygonVertices; ++i){
    k = (i + 1) % NumberOfPolygonVertices;
    for (int j = 0; j < NumberOfPolygonVertices; ++j){
      
      area += (bodyShape.m_vertices[k].x * bodyShape.m_vertices[j].y) - (bodyShape.m_vertices[j].x * bodyShape.m_vertices[k].y);
    }
    
  }
  if(area > 0)
  {
    // Reverse the order of the vertices
    
    
    
    reverseShape.m_vertexCount = bodyShape.m_vertexCount;
    
    for (int i = NumberOfPolygonVertices - 1, k = 0; i > -1; --i, ++k){
      
      reverseShape.m_vertices[i].Set(bodyShape.m_vertices[k].x, bodyShape.m_vertices[k].y);
    }		
    
    bodyShape = reverseShape;
    
  }
}
b2Vec2 StaticBody::getBodyPosition()
{
  return body->GetPosition();
}
void StaticBody::setBodyPosition(float positionX, float positionY)
{
  
  position = convert->convertObjectPointToGamePoint(positionX,positionY);
}

void StaticBody::drawPoint(float pos_x, float pos_y)
{
  glVertex2f(pos_x,pos_y);
}

void StaticBody::engageBody()
{
  bodyDef.type = b2_staticBody;
  bodyDef.position = position;
  fixtureDef.density = density;
  fixtureDef.friction = friction;
  fixtureDef.shape = &bodyShape;
  body = world->CreateBody(&bodyDef);
  body->CreateFixture(&fixtureDef);
}

void StaticBody::getUserData(void* userdata)
{
  body->SetUserData(userdata);
}
void StaticBody::setDensity(float density)
{
  this->density = density;
}
void StaticBody::setFriction(float friction)
{
  this->friction = friction;
}
void StaticBody::Update()
{
  GM_POINT* pos = convert->convertB2Vec2ToGM_Point(body->GetPosition());
  printf("TRANSLATED OVER TO :X[%4.2f] :Y[%4.2f]\n",pos->x,pos->y);
  glTranslatef(pos->x,pos->y,0.0f);
  glBegin(GL_POLYGON);
  for(int i =0; i < bodyShape.m_vertexCount; ++i)
  { 
    GM_POINT* pos_1 = convert->convertB2Vec2ToGM_Point(bodyShape.m_vertices[i]);
    printf("Body Draw Points : X[%4.2f]--Y[%4.2f]\n",pos_1->x,pos_1->y);
    drawPoint(pos_1->x,pos_1->y); 
    
  }
  glEnd();
}


StaticBody* StaticBody::returnBody()
{
  return this;
}

StaticBody::~StaticBody()
{
  
}


