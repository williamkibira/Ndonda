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


#include "convertutililty.h"

ConvertUtililty::ConvertUtililty(int mapHeight,int mapWidth)
{
this->mapHeight = mapHeight;
this->mapWidth = mapWidth;
}
b2Vec2 ConvertUtililty::convertObjectPointToGamePoint(int point_x, int point_y)
{
      return b2Vec2(point_x/getContextScaleFactor(),mapHeight - (point_y/getContextScaleFactor()));
}
b2Vec2 ConvertUtililty::convertPixelsToPoints(int point_x, int point_y)
{
    
   return b2Vec2(point_x/PIXEL_TO_METER,point_y/PIXEL_TO_METER);
}

b2Vec2 ConvertUtililty::convertPolyToGamePoint(int point_x, int point_y)
{
      return b2Vec2(point_x/getContextScaleFactor(),-point_y/getContextScaleFactor());
}

float ConvertUtililty::getContextScaleFactor()
{
    return 1.0f;
}
GM_POINT* ConvertUtililty::convertB2Vec2ToGM_Point(b2Vec2 point)
{     GM_POINT* Gpoint = new GM_POINT();
      Gpoint->x =(point.x*getContextScaleFactor()*PIXEL_TO_METER);
      Gpoint->y =(point.y*getContextScaleFactor()*PIXEL_TO_METER);
      
      //printf("GM_POINT : X->[%4.2f] Y->[%4.2f]\n",Gpoint->x,Gpoint->y);
      return Gpoint;
}
float ConvertUtililty::convertRadiansToDegrees(float radians)
{
  return   (180.0/3.141592653589793)*radians;
}
float ConvertUtililty::convertDegreesToRadians(float degrees)
{

  return (3.141592653589793/180)*degrees;
}

ConvertUtililty::~ConvertUtililty()
{

}

