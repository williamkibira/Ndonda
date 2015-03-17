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

#ifndef POLYGON_H
#define POLYGON_H
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <list>
#include <vector>
#include "../datatypes/vector2d.h"
class Polygon
{

public:
    
  Polygon(const std::vector<Vector2Df&>&Points,std::string picturePath, std::string name);
  Vector2Df& getEdge(int value);
  Vector2Df& getPointAt(int value);
  void drawDot(float radius,int segments,float x_pos,float y_pos);
  void updatePolygon(const Vector2Df& newPosition);
  Vector2Df& getCenter();
  void drawPolygon();
  int getEdgeCount();
  void buildEdges();
  void blitPicture();
  virtual ~Polygon();
private:
  std::vector<Vector2Df&> Points;
  std::list<Vector2Df&>edges;
  Vector2Df* center;
  std::string name;
  std::string picturePath;
};

#endif // POLYGON_H