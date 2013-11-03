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


#include "bridge.h"

Bridge::Bridge(b2World* world,b2Body* ground)
{
  this->ground = ground;
  this->world = world;
  N = 20;
  convert = new ConvertUtililty();
  construct();
  
}
void Bridge::construct()
{
  
  
  shape.SetAsBox(1.0f, 0.125f);
  
  
  fd.shape = &shape;
  fd.density = 1.0f;
  fd.friction = 0.6f;
  
  prevBody = ground;
  for (int32 i = 0; i < N; ++i)
  {
    
    bd.type = b2_dynamicBody;
    
    bd.position.Set(161.0f + 2.0f * i, -0.125f);
    
    body = world->CreateBody(&bd);
    
    body->CreateFixture(&fd);
    
    
    b2Vec2 anchor(160.0f + 2.0f * i, -0.125f);
    jd.Initialize(prevBody, body, anchor);
    world->CreateJoint(&jd);
    prevBody = body;
  }
  b2Vec2 anchor(160.0f + 2.0f * N, -0.125f);
  jd.Initialize(prevBody, ground, anchor);
  world->CreateJoint(&jd);
}

void Bridge::draw()
{
  for(b2Fixture* f = body->GetFixtureList(); f;f = f->GetNext())
  {
    b2PolygonShape* polyshape =(b2PolygonShape*) f->GetShape();
    for(int i = 0; i < polyshape->GetVertexCount(); ++i)
    {
      GM_POINT* point = convert->convertB2Vec2ToGM_Point(polyshape->m_vertices[i]);
      glVertex2f(point->x,point->y);
    }
  }
  
}


Bridge::~Bridge()
{
  
}

