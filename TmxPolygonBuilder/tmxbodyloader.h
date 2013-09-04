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
#include "staticbody.h"
#include "dynamicbody.h"
#include "groundbody.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <TmxParser/Tmx.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#ifndef TMXBODYLOADER_H
#define TMXBODYLOADER_H


class TmxBodyLoader
{

public:
    TmxBodyLoader(std::string filename,b2World* world);
  
  virtual ~TmxBodyLoader();
  void objectGroupResolver(const Tmx::ObjectGroup* objectGroup);
  int getScreenHeight();
  int getScreenWidth();
  std::vector<DynamicBody*> getDynamicBodies();
  std::vector<StaticBody*> getStaticBodies();
  
  
private:
  int positionX;
  int positionY;
  int numberOfPoints;
  
  b2World* world;
  int screenHeight;
  int screenWidth;
  std::vector<DynamicBody*> dynaBodys;
  std::vector<StaticBody*> staticBodys;
  std::vector<GroundBody*> groundBodys;
  ConvertUtililty* convert;
};

#endif // TMXBODYLOADER_H
