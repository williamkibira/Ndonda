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


#include "butida.h"

Butida::Butida(b2World* world)
{
  this->world = world;
  wall1 = new Wall(world,32,47,64,2);
  wall2 = new Wall(world,63,24,2,48);
  
  shape.SetAsBox(1.0f,0.5f);
  fd.shape = &shape;
  fd.density = 1.0f;
  fd.friction = 0.3f;
  
  bd.userData = this;
  bd.type = b2_dynamicBody;
  bd.position.Set(0,45);
  body = world->CreateBody(&bd);
  body->CreateFixture(&fd);
  deltaTime = 10.0f/60.0f;
  convert = new ConvertUtililty();
  
}
void Butida::target(int32 x, int32 y)
{       b2Vec2 mousepoint =  convertScreenToWorld(x,y);
  angle  = atan2f(mousepoint.y - body->GetPosition().y,mousepoint.x);  
  b2Vec2 plot(mousepoint.x,mousepoint.y - body->GetPosition().y);
  
  plotTrajectory(body->GetPosition(),plot);
}
float Butida::getAngle()
{
  return body->GetAngle();
}
b2Vec2 Butida::getPosition()
{
  return body->GetPosition();
}
b2Vec2 Butida::convertScreenToWorld(int32 x, int32 y)
{
  float32 u = x/float32(640);
  float32 v = (480 - y)/float32(480);
  float32 ratio = float32(640)/float32(480);
  b2Vec2 extends(ratio* PIXEL_TO_METER,PIXEL_TO_METER);
  extends *= (1.0f * PIXEL_TO_METER);
  b2Vec2 origin;
  origin.Set(0.0f,0.0f);
  b2Vec2 lower = origin - extends;
  b2Vec2 upper =  origin + extends;
  
  b2Vec2 pos;
  pos.x = (1.0f - u)*lower.x + u*upper.x;
  pos.y = (1.0f - v)*upper.y + v*upper.y;
  
  return pos;
  
}


void Butida::moveCatapult(int direction)
{
  b2Vec2 velocity = body->GetLinearVelocity(); 
  switch(direction)
  {
    case SDLK_w:{ float impulse = body->GetMass()* 100;
		  body->ApplyLinearImpulse(b2Vec2(0,impulse),body->GetWorldCenter()); 
		  break;}
    case SDLK_s:{  velocity.x *= 0.98;break;}
    case SDLK_a:{ velocity.x = b2Max(velocity.x -0.4f,-8.0f);break;}
    case SDLK_d:{ velocity.x = b2Min(velocity.x + 0.4f,8.0f);break;}
    
   // Get __ a fix for all of this ....
   
  }
  body->SetLinearVelocity(velocity);
}
void Butida::plotTrajectory(b2Vec2 init_pos, b2Vec2 target_pos)
{
  // take care of time lapse in hertz
  speed = 20.0f;
  // convert to angular velocity on given planes
  b2Vec2 velocity;
  velocity.x = cosf(angle)*speed;
  velocity.y = sinf(angle)*speed - ((9.8f)*deltaTime);
  float32 total_time = 20;
  int32 edgeDistance(0);
  b2Vec2 prev_pos(init_pos);
  currentTime = 0.0f;
  /***********************************************/
  /*ANIMATION SPRITE FOR THE PLOTTING OF THE DOTS*/
  /***********************************************/
 
  while(currentTime < total_time)
  {
  init_pos.x+= velocity.x * deltaTime;
  init_pos.y+= velocity.y * deltaTime;
  currentTime += deltaTime;
  velocity.y -= (9.8*deltaTime);
  if(distanceBetween(prev_pos,init_pos) > edgeDistance){
    /**********************************************/
    /*SPRITE DRAWING ALGORITHM [< COMING SOON >]  */
    /**********************************************/
    printf("Draw Trajectory Position is x[%f]:y[%f]\n",init_pos.x,init_pos.y);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f); // 
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(init_pos);
    glVertex2f(point->x,point->y);
    glEnd();
    glPointSize(1.0f);
   prev_pos = init_pos;
  edgeDistance += 2;
  }
  }
  
}
float Butida::distanceBetween(b2Vec2 a, b2Vec2 b)
{
 return  sqrtf(powf(a.x - b.x,2) + powf(a.y - b.y,2));
}

void Butida::shoot()
{
  ammo.push_back( new Stone(world,body->GetPosition(),angle));
}

float Butida::normalize(b2Vec2 velocity)
{
  return sqrtf(powf(velocity.x,2)+powf(velocity.y,2)); // useless methods 
}

Butida::~Butida()
{
    
}

