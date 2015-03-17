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

#include "../shapes/polygon.h"
#include "../datatypes/vector2d.h"
#include "collisionresult.h"
#include "../math/math2.h"
#include <math.h>
#include <limits>
#include <stdlib.h>
#include <stdio.h>


#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

class CollisionTest
{

public:
    CollisionTest();
    CollisionResult collisionTester(Polygon* polygonA,Polygon* polygonB,Vector2D* velocity);
    void ProjectPolygon(Polygon* polygon ,Vector2D* axis,float min,float max);
    float intervalDistance();
    virtual ~CollisionTest();
    
private:
  CollisionResult result;
  float minIntervalDistance;
  int edgeCountA;
  int edgeCountB;
  float minA,minB,maxA,maxB;
  float velocityProjection;
  float IntervalDistance;
  Vector2D* translationAxis;
  Vector2D* edge;
  Vector2D* dummy;
  Vector2D* axis;
};

#endif // COLLISIONTEST_H
