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

#include <Box2D/Box2D.h>
#include "Constants.h"
#include "GamePoint.h"
#include <stdio.h>

#ifndef CONVERTUTILILTY_H
#define CONVERTUTILILTY_H

class ConvertUtililty
{

public:
    ConvertUtililty(int mapHeight,int mapWidth);
    static float getContextScaleFactor();
    b2Vec2 convertPixelsToPoints(int point_x,int point_y);
    b2Vec2 convertPolyToGamePoint(int point_x,int point_y);
    b2Vec2 convertObjectPointToGamePoint(int point_x,int point_y);
    GM_POINT* convertB2Vec2ToGM_Point(b2Vec2 point);
    float convertRadiansToDegrees(float radians);
    float convertDegreesToRadians(float degrees);
    
    virtual ~ConvertUtililty();
private:
  int mapHeight;
  int mapWidth;
  GM_POINT* point;
};

#endif // CONVERTUTILILTY_H
