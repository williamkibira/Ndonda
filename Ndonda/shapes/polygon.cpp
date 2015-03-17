/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "shapes/polygon.h"

Polygon::Polygon(const std::vector<Vector2Df&>&Points,std::string picturePath, std::string name)
{
  this->Points = Points;
  float total_x,total_y;
  for(std::vector<Vector2Df&>::iterator iter = Points.begin(); iter != Points.end();++iter)
  {
    total_x += (*iter).x;
    total_y += (*iter).y;
  }
  center = new Vector2Df(total_x/Points.size(),total_y/Points.size());
  printf("THE CENTER OF THIS POLYGON IS X[%f]Y[%f]\n",center.x,center.y);
  buildEdges();
  this->picturePath = picturePath;
  this->name = name;
}

Vector2D& Polygon::getEdge(int value)
{
  std::list<Vector2D&>::iterator iter = edges.begin();
  std::advance(iter,value);
  return *iter;
}

Vector2Df& Polygon::getPointAt(int value)
{
  return Points.at(value);
}
void Polygon::updatePolygon(const Vector2Df& newPosition)
{
  for(std::vector<Vector2Df&>::iterator iter = Points.begin(); iter != Points.end(); ++iter)
  {
    (*iter).set(newPosition);
  }
}

int Polygon::getEdgeCount()
{
  return edges.size();
}

void Polygon::drawPolygon()
{
  glPushMatrix(); 
  
  glTranslatef(center->x,center->y,0.0f);
  glColor3f(1.0f,1.0f,1.0f);
  //drawDot(5.0f,50,center->get_x(),center->get_y());
  glBegin(GL_POLYGON);
  for(std::vector<Vector2D&>::iterator iter = Points.begin(); iter != Points.end(); ++iter)
  {
    glVertex2f((*iter).x,(*iter).y); 
    printf("POINTS ARE %4.2f %4.2f\n",(*iter).x,(*iter).y);
  }
  glEnd();
  glPopMatrix();
  for(std::vector<Vector2D*>::iterator iter = Points.begin(); iter != Points.end(); ++iter)
  { glPushMatrix();
  
  drawDot(10.0f,50,(*iter).x,(*iter).y); 
  glPopMatrix();
  }
  
}

void Polygon::drawDot(float radius, int segments, float x_pos, float y_pos)
{
  glTranslatef(x_pos,y_pos,0.0f);
  glBegin( GL_TRIANGLE_FAN );
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f(x_pos, y_pos);
  for( int n = 0; n <= segments; ++n ) {
    float const t = 2*M_PI*(float)n/(float)segments;
    glVertex2f(x_pos + sin(t)*radius, y_pos + cos(t)*radius);
  }
  glEnd();
}

void Polygon::buildEdges()
{
  Vector2Df p1;
  Vector2Df p2;
  
  for(int i = 0; i < Points.size();++i)
  {
    p1 = Points.at(i);
    if((i+1) >= Points.size())
    {
      p2 = Points.at(0);
    }else{
      
      p2 = Points.at(i + 1);
    } 
    p2->subtract(p1);
    edges.push_back(p2);
  }
  
}
void Polygon::blitPicture()
{
 // This Is Where the Picture of The Object Will be placed on screen
}


Vector2Df& Polygon::getCenter()
{
  return center;
}
Polygon::~Polygon()
{
  
}

