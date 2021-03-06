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


#include <Box2D/Box2D.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include "leg.h"
#include "balls.h"
#include "ground.h"
#ifndef THEOJANSEN_H
#define THEOJANSEN_H

class TheoJansen
{
  
public:
  TheoJansen(b2World* world);
  void construct();
  void set();
  void draw();
  b2Vec2 getPosition();
  void move(int key);
  float getAngle();
  virtual ~TheoJansen();
private:
  b2PolygonShape shape;
  b2FixtureDef sd;
  b2BodyDef bd;
  b2CircleShape shape1;
  b2RevoluteJointDef jd;
  // Parts
  b2Vec2 m_offset;
  b2Body* m_chassis;
  b2Body* m_wheel;
  b2RevoluteJoint* m_motorJoint;
  bool m_motorOn;
  float32 m_motorSpeed;
  b2World* m_world;
  b2Vec2 pivot;
  Leg* leg1;
  Leg* leg2;
  Leg* leg3;
  Leg* leg4;
  Leg* leg5;
  Leg* leg6;
  ConvertUtililty* convert;
  Balls* balls;
  Ground* ground;
};

#endif // THEOJANSEN_H
