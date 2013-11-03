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


#include <string>
#include <Box2D/Box2D.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <math.h>

#ifndef BODYCONSTRUCTOR_H
#define BODYCONSTRUCTOR_H

class BodyConstructor : public b2Draw
{
  
public:
  BodyConstructor();
  virtual ~BodyConstructor();
  void DrawPolygon(b2Vec2* vertices , int32 vertexCount, const b2Color& color);
  void DrawSolidPolygon(b2Vec2* vertices , int32 vertexCount, const b2Color& color);
  void DrawCircle(b2Vec2& center, float radius, const b2Color& color);
  void DrawSolidCircle(b2Vec2& center, float32 radius,b2Vec2& axis, const b2Color& color);
  void DrawSegment(b2Vec2& pt1, b2Vec2& pt2,const b2Color& color);
  void DrawString(int x, int y, const char string,...);
  void DrawTransform(const b2Transform& xf);
  void DrawAABB(b2AABB* aabb, const b2Color& color);
  void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
  void checkShape(b2Shape::Type shapetype);
  void getFixture(b2Fixture* fixture);
private:
  b2ChainShape* chainshape;
  b2CircleShape* circleshape;
  b2PolygonShape* polygonshape;
  b2EdgeShape* edgeshape;
  b2Fixture* fixture;
  
};

#endif // BODYCONSTRUCTOR_H