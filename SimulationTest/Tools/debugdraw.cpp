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


#include "debugdraw.h"

DebugDraw::DebugDraw()
{
  convert = new ConvertUtililty();
}
void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
  const float32 k_segments = 16.0f;
  const float32 k_increment = 2.0f * b2_pi / k_segments;
  float32 theta = 0.0f;
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINE_LOOP);
  for (int32 i = 0; i < k_segments; ++i)
  {
    b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(v);
    glVertex2f(point->x,point->y);
    theta += k_increment;
  }
  glEnd();
}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
  const float32 k_segments = 16.0f;
  const float32 k_increment = 2.0f * b2_pi / k_segments;
  float32 theta = 0.0f;
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
  glBegin(GL_TRIANGLE_FAN);
  for (int32 i = 0; i < k_segments; ++i)
  {
    b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(v);
    glVertex2f(point->x,point->y);
    theta += k_increment;
  }
  glEnd();
  glDisable(GL_BLEND);
  
  theta = 0.0f;
  glColor4f(color.r, color.g, color.b, 1.0f);
  glBegin(GL_LINE_LOOP);
  for (int32 i = 0; i < k_segments; ++i)
  {
    b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(v);
    glVertex2f(point->x,point->y);
    theta += k_increment;
  }
  glEnd();
  
  b2Vec2 p = center + radius * axis;
  glBegin(GL_LINES);
  
  GM_POINT* pointcenter =  convert->convertB2Vec2ToGM_Point(center);
  GM_POINT* p_point =  convert->convertB2Vec2ToGM_Point(p);
  
  
  glVertex2f(pointcenter->x,pointcenter->y);
  glVertex2f(p_point->x, p_point->y);
  glEnd();
}
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINE_LOOP);
  for (int32 i = 0; i < vertexCount; ++i)
  {
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(vertices[i]);
    glVertex2f(point->x,point->y);
  }
  glEnd();
}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
  glBegin(GL_TRIANGLE_FAN);
  for (int32 i = 0; i < vertexCount; ++i)
  {
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(vertices[i]);
    glVertex2f(point->x,point->y);
  }
  glEnd();
  glDisable(GL_BLEND);
  
  glColor4f(color.r, color.g, color.b, 1.0f);
  glBegin(GL_LINE_LOOP);
  for (int32 i = 0; i < vertexCount; ++i)
  {
    GM_POINT* point =  convert->convertB2Vec2ToGM_Point(vertices[i]);
    glVertex2f(point->x,point->y);
  }
  glEnd();
}
void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
  glPointSize(size);
  glBegin(GL_POINTS);
  glColor3f(color.r, color.g, color.b);
  GM_POINT* point =  convert->convertB2Vec2ToGM_Point(p);
  glVertex2f(point->x,point->y);
  glEnd();
  glPointSize(1.0f);
}
void DebugDraw::DrawTransform(const b2Transform& xf)
{
  b2Vec2 p1 = xf.p, p2;
  const float32 k_axisScale = 0.4f;
  glBegin(GL_LINES);
  
  glColor3f(1.0f, 0.0f, 0.0f);
  GM_POINT* point1 =  convert->convertB2Vec2ToGM_Point(p1);
  glVertex2f(point1->x,point1->y);
  
  p2 = p1 + k_axisScale * xf.q.GetXAxis();
  GM_POINT* point2 =  convert->convertB2Vec2ToGM_Point(p2);
  glVertex2f(point2->x,point2->y);
  
  
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2f(point1->x,point1->y);
  p2 = p1 + k_axisScale * xf.q.GetYAxis();
  glVertex2f(point2->x,point2->y);
  
  glEnd();
}
void DebugDraw::DrawSegment(const b2Vec2& pt1, const b2Vec2& pt2, const b2Color& color)
{
  GM_POINT* point1 =  convert->convertB2Vec2ToGM_Point(pt1);
 
  GM_POINT* point2 =  convert->convertB2Vec2ToGM_Point(pt2);
  
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINES);
  glVertex2f(point1->x, point1->y);
  glVertex2f(point2->x, point2->y);
  glEnd();
}
void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINE_LOOP);
  glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
  glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
  glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
  glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
  glEnd();
}
void DebugDraw::checkShape(b2Shape::Type shapetype)
{
  switch(shapetype)
  {
    case b2Shape::e_chain:{	chainshape = (b2ChainShape*)fixture->GetShape(); break;}
    case b2Shape::e_circle:{	circleshape = (b2CircleShape*)fixture->GetShape(); break;}
    case b2Shape::e_edge:{	edgeshape = (b2EdgeShape*)fixture->GetShape(); break;}
    case b2Shape::e_polygon:{	 polygonshape = (b2PolygonShape*)fixture->GetShape(); break;}
    case b2Shape::e_typeCount:{	  break;}  
  }
}
void DebugDraw::getFixture(b2Fixture* fixture)
{

}

DebugDraw::~DebugDraw()
{

}

