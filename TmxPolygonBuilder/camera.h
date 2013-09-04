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


#include <SDL2/SDL_opengl.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "convertutililty.h"
#include <math.h>

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{

public:
    Camera(int screenHeight,int screenWidth);
    void setCameraPosition(b2Vec2 characterPOS,float angle);
    void setCharacterSize(float character_width,float character_height);
    void rotationResolver(float x_position,float y_position);
    void zoomCameraOnPlayer(float zoomFactor);
    virtual ~Camera();
private:
  
float x_position;
float x_previous_position;
float y_previous_position;
float y_position;
float x_angle;
float y_angle;

b2Vec2 characterPOS;

int screenHeight;
int screenWidth;
float character_width;
float character_height;
ConvertUtililty *convert;
};

#endif // CAMERA_H
