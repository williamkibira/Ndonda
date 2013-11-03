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


#include "theojansen.h"

TheoJansen::TheoJansen(b2World* world)
{ 
  this->m_world = world;
  m_offset.Set(0.0f, 8.0f);
  m_motorSpeed = 2.0f;
  m_motorOn = true;
  pivot.Set(0.0f, 0.8f);
  
  construct();
  
  
  leg1 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  leg2 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  leg3 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  leg4 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  leg5 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  leg6 = new Leg(m_world,m_offset,m_chassis,m_wheel,m_motorJoint);
  set();
  
  ground = new Ground(world);
  balls = new Balls(world);
}
void TheoJansen::construct()
{
  // Chassis
  
  
  shape.SetAsBox(2.5f, 1.0f);
  
  
  sd.density = 1.0f;
  sd.shape = &shape;
  sd.filter.groupIndex = -1;
  
  bd.type = b2_dynamicBody;
  bd.position = pivot + m_offset;
  m_chassis = m_world->CreateBody(&bd);
  m_chassis->CreateFixture(&sd);
  
  // Wheel
  
  
  shape1.m_radius = 1.6f;
  
  
  sd.density = 1.0f;
  sd.shape = &shape1;
  sd.filter.groupIndex = -1;
  
  bd.type = b2_dynamicBody;
  bd.position = pivot + m_offset;
  m_wheel = m_world->CreateBody(&bd);
  m_wheel->CreateFixture(&sd);
  
  
  jd.Initialize(m_wheel, m_chassis, pivot + m_offset);
  jd.collideConnected = false;
  jd.motorSpeed = m_motorSpeed;
  jd.maxMotorTorque = 400.0f;
  jd.enableMotor = m_motorOn;
  m_motorJoint = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
  
  
}
void TheoJansen::set()
{
  b2Vec2 wheelAnchor;
  wheelAnchor = pivot + b2Vec2(0.0f, -0.8f);
  
  leg1->createleg(-1.0f, wheelAnchor);
  leg2->createleg(1.0f, wheelAnchor);
  
  m_wheel->SetTransform(m_wheel->GetPosition(), 120.0f * b2_pi / 180.0f);
  leg3->createleg(-1.0f, wheelAnchor);
  leg4->createleg(1.0f, wheelAnchor);
  
  m_wheel->SetTransform(m_wheel->GetPosition(), -120.0f * b2_pi / 180.0f);
  leg5->createleg(-1.0f, wheelAnchor);
  leg6->createleg(1.0f, wheelAnchor);
}
void TheoJansen::draw()
{
  
  // Draw the chassis
  GM_POINT* pos = convert->convertB2Vec2ToGM_Point(m_chassis->GetPosition());
  glTranslatef(pos->x,pos->y,0.0f);
  glRotatef(convert->convertRadiansToDegrees(m_chassis->GetAngle()),0.0f,0.0f,1.0f);
  glPushMatrix();
  glBegin(GL_POLYGON);
  {
    glVertex2f(-(2.5f*0.5f)*PIXEL_TO_METER + pos->x,(1.0f*0.5f)*PIXEL_TO_METER + pos->y);
    glVertex2f((2.5f*0.5f)*PIXEL_TO_METER + pos->x,(1.0f*0.5f)*PIXEL_TO_METER + pos->y);
    glVertex2f((2.5f*0.5f)*PIXEL_TO_METER + pos->x,-(1.0f*0.5f)*PIXEL_TO_METER + pos->y);
    glVertex2f(-(2.5f*0.5f)*PIXEL_TO_METER + pos->x,-(1.0f*0.5f)*PIXEL_TO_METER + pos->y);
  }
  glEnd();
  glPopMatrix();
  // Draw the circle
  
  int segments = 50;
  GM_POINT* pos_c = convert->convertB2Vec2ToGM_Point(m_wheel->GetPosition());
  glTranslatef(pos_c->x,pos_c->y,0.0f);
  glRotatef(convert->convertRadiansToDegrees(m_wheel->GetAngle()),0.0f,0.0f,1.0f);
  glPushMatrix();
  glColor3f(1.0f,0.0f,1.0f);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2f(pos_c->x, pos_c->y);
  for( int n = 0; n <= segments; ++n ) {
    float const t = 2*M_PI*(float)n/(float)segments;
    glVertex2f(pos->x + sin(t)*shape.m_radius*PIXEL_TO_METER, pos->y + cos(t)*shape.m_radius*PIXEL_TO_METER);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  leg1->drawleg();
  leg2->drawleg();
  leg3->drawleg();
  leg4->drawleg();
  leg5->drawleg();
  leg6->drawleg();
  glPopMatrix();
}
float TheoJansen::getAngle()
{
  return m_chassis->GetAngle();
}
b2Vec2 TheoJansen::getPosition()
{
  return m_chassis->GetPosition();
}

void TheoJansen::move(int key)
{
  
  switch (key)
  {
    case SDLK_a:
      m_motorJoint->SetMotorSpeed(-m_motorSpeed);
      break;
      
    case SDLK_s:
      m_motorJoint->SetMotorSpeed(0.0f);
      break;
      
    case SDLK_d:
      m_motorJoint->SetMotorSpeed(m_motorSpeed);
      break;
      
    case SDLK_m:
      m_motorJoint->EnableMotor(!m_motorJoint->IsMotorEnabled());
      break;
  }
}

TheoJansen::~TheoJansen()
{
  
}



