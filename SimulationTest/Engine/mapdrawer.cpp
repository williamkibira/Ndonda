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


#include "mapdrawer.h"

MapDrawer::MapDrawer(Tmx::Map* map)
{

  if(map->HasError()) {
    printf("[Error]::Map(%d) %s\n", map->GetErrorCode(), map->GetErrorText().c_str()); 
    exit(0);
  }
  leveldata.screen_width = map->GetWidth()*map->GetTileWidth();
  leveldata.screen_height = map->GetHeight()*map->GetTileHeight();
  imageDrawer = new GraphicsMgr();
}
LevelData MapDrawer::getLevelSize()
{
  return leveldata;
}

void MapDrawer::renderMap()
{
  
  //Break up the map by layers
  for (int l = 0; l < map->GetNumLayers(); ++l) {
    const Tmx::Layer *layer = map->GetLayer(l);
    printf("Layer Iterate (%d)\n",l);
    //Break up the layers by tilesets
    for(int t = 0; t < map->GetNumTilesets(); ++t) {
      printf("TileSet Iterate (%d)\n",t);
      DrawableLayer* d_layer = new DrawableLayer(imageDrawer);
      printf("created Object \n");
  
  d_layer->LoadSet(layer, map->GetTileset(t));
  printf("load Data\n");
  layers.push_back(d_layer);
  
    }
    
  }  
  
  
  
}


MapDrawer::~MapDrawer()
{

}

