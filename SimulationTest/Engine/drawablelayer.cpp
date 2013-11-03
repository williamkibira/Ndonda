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


#include "drawablelayer.h"

DrawableLayer::DrawableLayer(GraphicsMgr* imageDraw)
{
  tileset_index = 0;
  tile_width = 0;
  tile_height = 0;
  tile_spacing = 0;
  tile_margin = 0;
  tileU = 0;
  tileV = 0;
  this->imageDraw = imageDraw;
}

bool DrawableLayer::LoadSet(const Tmx::Layer* layer, const Tmx::Tileset* tileset)
{
  if(layer == NULL || tileset == NULL)
  {
    printf("DATA IN LAYER OR TILESET NULL\n");
    return false;
  }
  printf("LAYER LOADED SUCCESSFULLY\n");
  /*******************************/
  /*RUN THROUGH THE LAYER DATA   */
  /*******************************/
  
  
  SDL_Texture* texture = imageDraw->surfaceToTexture(tileset->GetImage()->GetSource());
  printf("Texture Is %d\n",texture);
  // Conversion of the Texture in the Tile Map.
  SDL_GL_BindTexture(texture, (float*)tileset->GetImage()->GetWidth(), (float*)tileset->GetImage()->GetHeight()); 
  
  // Iteration through the tile layer
  for(int y = 0; y < layer->GetHeight(); ++y)
  {
    for(int x = 0; x < layer->GetWidth(); ++x)
    {
      // Get the tileID
      tileID = layer->GetTileId(x, y);
      printf("TILE ID: %d\n" ,tileID);
  if(!inTileSet(tileID, tileset)) {
    //Tile does not belong to our tileset, do not draw
    //printf("TILESET NOT BELONG\n");
    continue;
  }
  // Get The tileset  Index
  
  tileset_index = layer->GetTileTilesetIndex(x, y);
  
  tile_width = tileset->GetTileWidth();
  tile_height = tileset->GetTileHeight();
  tile_spacing = tileset->GetSpacing();
  tile_margin = tileset->GetMargin();
  
  // GET THE TILE CO-ORDINATES
  tileID -= tileset->GetFirstGid();
  tileU = tileID % ((tileset->GetImage()->GetWidth() - tile_margin) 
  / (tile_width + tile_spacing));
  tileV = tileID / ((tileset->GetImage()->GetWidth() - tile_margin) 
  / (tile_width + tile_spacing));
  // CLIP THE IMAGE FOR THE TILE BASED ON THE DATA AQUIRED
  
  /**************************************************************/
  /* THIS COULD BE SDL RECT / GLQUAD OR SOMETHING ESLE*/
  /**************************************************************/
  //glTranslatef((GLfloat)tileU,(GLfloat)tileV,0.0f);
  glBegin( GL_QUADS );
  
  
  //define its 4 texture coordinates
  glTexCoord2f(tileU * (tile_width + tile_spacing) + tile_margin, 
	       tileV * (tile_height + tile_spacing) + tile_margin);
  glVertex2f(x * tile_width, y * tile_height);
  
  
  glTexCoord2f((tileU + 1) * (tile_width + tile_spacing) + tile_margin 
  - tile_spacing, tileV * (tile_height + tile_spacing) + tile_margin);
  glVertex2f((x + 1) * tile_width, y * tile_height);
  
  glTexCoord2f((tileU + 1) * (tile_width + tile_spacing) + tile_margin 
  - tile_spacing, (tileV + 1) * (tile_height + tile_spacing) + tile_margin - tile_spacing);
  glVertex2f((x + 1) * tile_width, (y + 1) * tile_height);   
  
  glTexCoord2f(tileU * (tile_width + tile_spacing) + tile_margin, 
	       (tileV + 1) * (tile_height + tile_spacing) + tile_margin - tile_spacing);  
  glVertex2f(x * tile_width, (y + 1) * tile_height);            
  
  glEnd();
  
  
    }
  }
  
}
  bool DrawableLayer::inTileSet(int tile_ID, const Tmx::Tileset* tileset)
  {
    int tiles_x = (tileset->GetImage()->GetWidth() - tileset->GetMargin()) / (tileset->GetTileWidth() + tileset->GetSpacing());
    int tiles_y = (tileset->GetImage()->GetHeight() - tileset->GetMargin()) / (tileset->GetTileHeight() + tileset->GetSpacing());
    int total_tiles = tiles_x * tiles_y;
    
    if((tile_ID >= tileset->GetFirstGid()) && (tile_ID <= tileset->GetFirstGid() + total_tiles)) {
      return true;
    }
    
    return false;
    
  } 
  
  

DrawableLayer::~DrawableLayer()
{

}

