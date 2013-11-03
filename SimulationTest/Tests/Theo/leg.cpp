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


#include "leg.h"

Leg::Leg(b2World* world,b2Vec2 m_offset,b2Body* chassis,b2Body* m_wheel,b2RevoluteJoint* m_motorJoint)
{
  m_world = world;
  this->m_offset = m_offset;
  this->m_chassis = chassis;
  this->m_wheel = m_wheel;
  this->m_motorJoint;
}

void Leg::createleg(float32 s, const b2Vec2& wheelAnchor)
{
  b2Vec2 p1(5.4f * s, -6.1f);
  b2Vec2 p2(7.2f * s, -1.2f);
  b2Vec2 p3(4.3f * s, -1.9f);
  b2Vec2 p4(3.1f * s, 0.8f);
  b2Vec2 p5(6.0f * s, 1.5f);
  b2Vec2 p6(2.5f * s, 3.7f);
  
  
  fd1.filter.groupIndex = -1;
  fd2.filter.groupIndex = -1;
  fd1.density = 1.0f;
  fd2.density = 1.0f;
  
  
  
  if (s > 0.0f)
  {
    b2Vec2 vertices[3];
    
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    poly1.Set(vertices, 3);
    
    vertices[0] = b2Vec2_zero;
    vertices[1] = p5 - p4;
    vertices[2] = p6 - p4;
    poly2.Set(vertices, 3);
  }
  else
  {
    b2Vec2 vertices[3];
    
    vertices[0] = p1;
    vertices[1] = p3;
    vertices[2] = p2;
    poly1.Set(vertices, 3);
    
    vertices[0] = b2Vec2_zero;
    vertices[1] = p6 - p4;
    vertices[2] = p5 - p4;
    poly2.Set(vertices, 3);
  }
  
  fd1.shape = &poly1;
  fd2.shape = &poly2;
  
  b2BodyDef bd1, bd2;
  bd1.type = b2_dynamicBody;
  bd2.type = b2_dynamicBody;
  bd1.position = m_offset;
  bd2.position = p4 + m_offset;
  
  bd1.angularDamping = 10.0f;
  bd2.angularDamping = 10.0f;
  
  b2Body* body1 = m_world->CreateBody(&bd1);
  b2Body* body2 = m_world->CreateBody(&bd2);
  
  body1->CreateFixture(&fd1);
  body2->CreateFixture(&fd2);
  
  b2DistanceJointDef djd;
  
  // Using a soft distance constraint can reduce some jitter.
  // It also makes the structure seem a bit more fluid by
  // acting like a suspension system.
  djd.dampingRatio = 0.5f;
  djd.frequencyHz = 10.0f;
  
  djd.Initialize(body1, body2, p2 + m_offset, p5 + m_offset);
  m_world->CreateJoint(&djd);
  
  djd.Initialize(body1, body2, p3 + m_offset, p4 + m_offset);
  m_world->CreateJoint(&djd);
  
  djd.Initialize(body1, m_wheel, p3 + m_offset, wheelAnchor + m_offset);
  m_world->CreateJoint(&djd);
  
  djd.Initialize(body2, m_wheel, p6 + m_offset, wheelAnchor + m_offset);
  m_world->CreateJoint(&djd);
  
  b2RevoluteJointDef rjd;
  
  rjd.Initialize(body2, m_chassis, p4 + m_offset);
  m_world->CreateJoint(&rjd);
}
void Leg::drawleg()
{
  glTranslatef(poly1.m_centroid.x*PIXEL_TO_METER,poly1.m_centroid.y*PIXEL_TO_METER,0.0f);
  glBegin(GL_POLYGON);
  for(int i = 0; i < poly1.GetVertexCount(); ++i)
  {
    glVertex2f(poly1.m_vertices[i].x*PIXEL_TO_METER,poly1.m_vertices[i].y*PIXEL_TO_METER);
    
  }
  glEnd();
  
  glTranslatef(poly2.m_centroid.x*PIXEL_TO_METER,poly2.m_centroid.y*PIXEL_TO_METER,0.0f);
  glBegin(GL_POLYGON);
  for(int i = 0; i < poly2.GetVertexCount(); ++i)
  {
    glVertex2f(poly2.m_vertices[i].x*PIXEL_TO_METER,poly2.m_vertices[i].y*PIXEL_TO_METER);
    
  }
  glEnd();
}


Leg::~Leg()
{
  
}


