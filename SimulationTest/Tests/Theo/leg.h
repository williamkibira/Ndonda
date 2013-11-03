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




#include <SDL2/SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "../../Settings/constants.h"
#include "../../Tools/convertutililty.h"
#include "../../Settings/gamepoint.h"
#ifndef LEG_H
#define LEG_H

class Leg
{
  
public:
  Leg(b2World* world,b2Vec2 m_offset,b2Body* chassis,b2Body* m_wheel,b2RevoluteJoint* m_motorJoint);
  void createleg(float32 s, const b2Vec2& wheelAnchor);
  void drawleg();
  virtual ~Leg();
private:
  b2FixtureDef fd1, fd2;
  b2PolygonShape poly1, poly2;
  b2Vec2 m_offset;
  b2World* m_world;
  b2Body* m_chassis;
  b2Body* m_wheel;
  b2RevoluteJoint* m_motorJoint;
  ConvertUtililty* convert;
};

#endif // LEG_H

