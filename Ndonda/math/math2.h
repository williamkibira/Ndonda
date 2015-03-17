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

#include <math.h>

#ifndef MATH2_H
#define MATH2_H

#define _USE_MATH_DEFINES

class Math2
{
  
public:
  Math2();
  static float radianOf(float angle);
  static float degreeOf(float radian);
  static float pythogras(float x_distance,float y_distance);
  static float cosineRule(float a,float b,float c);
  static float implementBound(float lowerBound,float upperBound, float number);
  virtual ~Math2();
  
private:
  float angle;
  
};


#endif // MATH2_H
