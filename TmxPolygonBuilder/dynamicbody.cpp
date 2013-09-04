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


#include "dynamicbody.h"

DynamicBody::DynamicBody(b2World* world, float positionX,float positionY,const Tmx::Polygon* polygon,ConvertUtililty* convert):Body(world,positionX,positionY)
{ this->convert = convert;
  density = 1;
  friction = 0.3;
  bodyShape.m_vertexCount = polygon->GetNumPoints();
 
  
  for(int i =0; i <  polygon->GetNumPoints();  ++i)
  {
    printf("CREATING BODY VERTICES\n");
    const Tmx::Point point = polygon->GetPoint(i);
    //bodyShape.m_vertices[i].Set(point.x/PIXEL_TO_METER,point.y/PIXEL_TO_METER);
      bodyShape.m_vertices[i] = convert->convertPixelsToPoints(point.x,point.y);
  }
   printf("DONE CREATING VERTICES\n");
  CCWT();
}
void DynamicBody::CCWT()
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
		   printf("IN AREA ZONE FAILURE\n");         
	      reverseShape.m_vertexCount = bodyShape.m_vertexCount;
	      
	      for (int i = NumberOfPolygonVertices - 1, k = 0; i > -1; --i, ++k){
	      
          reverseShape.m_vertices[i].Set(bodyShape.m_vertices[k].x, bodyShape.m_vertices[k].y);
        }		

        bodyShape = reverseShape;
		      
        }
}

void DynamicBody::drawPoint(float pos_x, float pos_y)
{
    glVertex2f(pos_x,pos_y);
}

b2Vec2 DynamicBody::getBodyPosition()
{
  return body->GetPosition();
}
void DynamicBody::setBodyPosition(float positionX, float positionY)
{
  //position.x = positionX;
  //position.y = positionY;
    position = convert->convertObjectPointToGamePoint(positionX,positionY);
}

void DynamicBody::engageBody()
{
 bodyDef.type = b2_dynamicBody;
 bodyDef.position = position;
 fixtureDef.shape = &bodyShape;
 fixtureDef.density = density;
 fixtureDef.friction = friction;
 body = world->CreateBody(&bodyDef);
 body->CreateFixture(&fixtureDef);
 
 
}

void DynamicBody::setDensity(float density)
{
 this->density = density;
}
void DynamicBody::setFriction(float friction)
{
 this->friction = friction;
}
void DynamicBody::getUserData(void* userdata)
{
 body->SetUserData(userdata);
}

DynamicBody* DynamicBody::returnBody()
{
  return this;
}
void DynamicBody::Update()
{ 
     GM_POINT* pos = convert->convertB2Vec2ToGM_Point(body->GetPosition());
      printf("TRANSLATED OVER TO :X[%4.2f] :Y[%4.2f]\n",pos->x,pos->y);
     glTranslatef(pos->x,pos->y,0.0f);
   glBegin(GL_POLYGON);
   glColor3f(0.0,1.0,0.0);
   float x = 0.0, y = 30.0;
   for(int i =0; i < bodyShape.m_vertexCount; ++i)
   { 
       GM_POINT* pos_1 = convert->convertB2Vec2ToGM_Point(bodyShape.m_vertices[i]);
       printf("Body Draw Points : X[%4.2f]--Y[%4.2f]\n",pos_1->x,pos_1->y);
       drawPoint(pos_1->x,pos_1->y); 
       glColor3f(1.0,0.0,0.0); glVertex2f(x, y+90.0);
       glColor3f(0.0,1.0,0.0); glVertex2f(x+90.0, y-90.0);
       glColor3f(0.0,0.0,1.0); glVertex2f(x-90.0, y-90.0);
   }
   glEnd();
}

DynamicBody::~DynamicBody()
{

}

