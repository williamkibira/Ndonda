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
#include <SDL2/SDL_opengl.h>
#include "../../Tools/convertutililty.h"
#include <math.h>
#include <SDL2/SDL_keycode.h>
#include "../../Input/input.h"
#include "../../Settings/constants.h"
#include <vector>
#include "wall.h"
#include "stone.h"

#ifndef BUTIDA_H
#define BUTIDA_H

class Butida
{

public:
    Butida(b2World* world);
    void moveCatapult(int direction);
    b2Vec2 getPosition();
    float getAngle();
    void target(int32 x,int32 y);
    void shoot();
    float normalize(b2Vec2 velocity);
    float distanceBetween(b2Vec2 a ,b2Vec2 b);
    // This method does not belong here
    void plotTrajectory(b2Vec2 init_pos,b2Vec2 target_pos);
    b2Vec2 convertScreenToWorld(int32 x, int32 y);
    virtual ~Butida();
private:
b2World* world;
b2Body* body;
b2BodyDef bd;
b2FixtureDef fd;
b2PolygonShape shape;
std::vector<Stone*> ammo;
std::vector<Stone*>::iterator ammo_iter;
bool empty;
Wall* wall1;
Wall* wall2;
float angle;
Stone* temp;
float32 speed;

// Trajectory properties

float32 deltaTime;
float32 currentTime;
ConvertUtililty* convert;
b2Vec2 current_position;
};

#endif // BUTIDA_H
