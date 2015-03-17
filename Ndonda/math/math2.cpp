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

#include "math/math2.h"

Math2::Math2()
{
  
}
float Math2::degreeOf(float radian)
{
  return (radian/M_PI)*180;
}
float Math2::radianOf(float angle)
{
  return (angle/180)*M_PI;
}
float Math2::pythogras(float x_distance, float y_distance)
{
  return sqrt(pow(x_distance,2) + pow(y_distance,2));
}

float Math2::cosineRule(float a, float b, float c)
{
  return (pow(b,2)+pow(c,2) - pow(a,2))/(2*b*c);
}

float Math2::implementBound(float lowerBound, float upperBound, float number)
{
  return fmin(fmax(lowerBound,number),upperBound);
}

Math2::~Math2()
{
  
}




