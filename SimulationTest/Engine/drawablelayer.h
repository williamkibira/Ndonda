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
#include <TmxParser/Tmx.h>
#include "graphicsmgr.h"

#ifndef DRAWABLELAYER_H
#define DRAWABLELAYER_H

class DrawableLayer
{

public:
  DrawableLayer(GraphicsMgr* imageDraw);
  bool LoadSet(const Tmx::Layer* layer, const Tmx::Tileset* tileset);
  bool inTileSet(int tile_ID, const Tmx::Tileset* tileset);
    virtual ~DrawableLayer();
private:
  int tileset_index;
  unsigned int tileID;
  // The Tile Measures
  int tile_width;
  int tile_height;
  int tile_spacing;
  int tile_margin;
  // The Tile Co-Ordinates
  int tileU;
  int tileV;
  //GraphicsMgr Holder
  GraphicsMgr* imageDraw;
};

#endif // DRAWABLELAYER_H
