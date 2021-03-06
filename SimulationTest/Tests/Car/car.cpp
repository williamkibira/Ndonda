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


#include "car.h"

Car::Car(b2World* world)
{
  m_hz = 4.0f;
  m_zeta = 0.7f;
  m_speed = 50.0f;
  ground = new Ground0(world);
  teeter = new Teeter(world,ground->getBody());
  bridge = new Bridge(world,ground->getBody());
  box = new Box(world);
  this->world = world;
  convert = new ConvertUtililty();
  buildcar();
  engagecar();
}
void Car::buildcar()
{
  
  b2Vec2 vertices[8];
  vertices[0].Set(-1.5f, -0.5f);
  vertices[1].Set(1.5f, -0.5f);
  vertices[2].Set(1.5f, 0.0f);
  vertices[3].Set(0.0f, 0.9f);
  vertices[4].Set(-1.15f, 0.9f);
  vertices[5].Set(-1.5f, 0.2f);
  chassis.Set(vertices, 6);
  
  
  circle.m_radius = 0.4f;
  
  bd.type = b2_dynamicBody;
  bd.position.Set(0.0f, 1.0f);
  m_car = world->CreateBody(&bd);
  m_car->CreateFixture(&chassis, 1.0f);
  
  fd.shape = &circle;
  fd.density = 1.0f;
  fd.friction = 0.9f;
  
  bd.position.Set(-1.0f, 0.35f);
  m_wheel1 = world->CreateBody(&bd);
  m_wheel1->CreateFixture(&fd);
  
  bd.position.Set(1.0f, 0.4f);
  m_wheel2 = world->CreateBody(&bd);
  m_wheel2->CreateFixture(&fd);
  
  
  axis.Set(0.0f, 1.0f);
  
  
}

void Car::move(int key)
{
  switch (key)
  {
    case SDLK_a:
      m_spring1->SetMotorSpeed(m_speed);
      break;
      
    case SDLK_s:
      m_spring1->SetMotorSpeed(0.0f);
      break;
      
    case SDLK_d:
      m_spring1->SetMotorSpeed(-m_speed);
      break;
      
    case SDLK_q:
      m_hz = b2Max(0.0f, m_hz - 1.0f);
      m_spring1->SetSpringFrequencyHz(m_hz);
      m_spring2->SetSpringFrequencyHz(m_hz);
      break;
      
    case SDLK_e:
      m_hz += 1.0f;
      m_spring1->SetSpringFrequencyHz(m_hz);
      m_spring2->SetSpringFrequencyHz(m_hz);
      break;
  }
}

void Car::engagecar()
{
  jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
  jd.motorSpeed = 0.0f;
  jd.maxMotorTorque = 20.0f;
  jd.enableMotor = true;
  jd.frequencyHz = m_hz;
  jd.dampingRatio = m_zeta;
  m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);
  
  jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
  jd.motorSpeed = 0.0f;
  jd.maxMotorTorque = 10.0f;
  jd.enableMotor = false;
  jd.frequencyHz = m_hz;
  jd.dampingRatio = m_zeta;
  m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);
}
b2Vec2 Car::getPosition()
{
  return m_car->GetPosition();
}
float Car::getAngle()
{
  return m_car->GetAngle();
}

void Car::draw()
{ 
  // Draw Chassis 
  GM_POINT* pos = convert->convertB2Vec2ToGM_Point(m_car->GetPosition());
  glPushMatrix();
  glTranslatef(pos->x,pos->y,0.0f);
  // glRotatef(convert->convertRadiansToDegrees(m_car->GetAngle()),0.0f,0.0f,1.0f);
  glBegin(GL_POLYGON);
  for(int i = 0; i < chassis.m_vertexCount; ++i)
  {
    glVertex2f(chassis.m_vertices[i].x*PIXEL_TO_METER,chassis.m_vertices[i].y*PIXEL_TO_METER); 
  }
  glEnd();
  
  // Draw the wheels
  // wheel 1
  drawWheel(convert->convertB2Vec2ToGM_Point(m_wheel1->GetPosition()),0.4f*PIXEL_TO_METER,m_wheel1->GetAngle());
  
  //wheel 2
  drawWheel(convert->convertB2Vec2ToGM_Point(m_wheel2->GetPosition()),0.4f*PIXEL_TO_METER,m_wheel2->GetAngle());
  
  glPopMatrix(); 
}
void Car::drawWheel(GM_POINT* pos,float radius,float angle)
{
  int segments = 50;
  glTranslatef(pos->x,pos->y,0.0f);
  //glRotatef(convert->convertRadiansToDegrees(angle),0.0f,0.0f,1.0f);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2f(pos->x, pos->y);
  for( int n = 0; n <= segments; ++n ) {
    float const t = 2*M_PI*(float)n/(float)segments;
    glVertex2f(pos->x + sin(t)*radius, pos->y + cos(t)*radius);
  }
  glEnd();
}

Car::~Car()
{
  
}



