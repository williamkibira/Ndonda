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


#include "textrenderer.h"

TextRenderer::TextRenderer(int screenwidth,int screenheight,SDL_Renderer* gRenderer)
{
  this->screenwidth = screenwidth;
  this->screenheight = screenheight;
  this->gRenderer = gRenderer;
  
  if(TTF_Init()== -1)
  {
    printf("SDL_TTF FAILED TO INITIALIZE %s\n",TTF_GetError());
  }
  loadFont("../Resources/lazy.ttf");
}
bool TextRenderer::loadFont(std::string path)
{
  gFont = TTF_OpenFont(path.c_str(),28);
  if(!gFont){
    printf("Error on loadingFont\n");
  }
}

bool TextRenderer::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
  //Get rid of preexisting texture
  free();
  
  //Render text surface
  SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
  if( textSurface == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  else
  {
    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    if( mTexture == NULL )
    {
      printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
      //Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }
    
    //Get rid of old surface
    SDL_FreeSurface( textSurface );
  }
  
  //Return success
  return mTexture != NULL;
}

void TextRenderer::setAlpha(Uint8 alpha)
{
  //Modulate texture alpha
  SDL_SetTextureAlphaMod( mTexture, alpha );
}
void TextRenderer::free()
{
  //Free texture if it exists
  if( mTexture != NULL )
  {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}
void TextRenderer::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  
  //Set clip rendering dimensions
  if( clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  
  //Render to screen
  SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
int TextRenderer::getHeight()
{

}
int TextRenderer::getWidth()
{

}
void TextRenderer::showText(std::string text)
{
  SDL_Color textColor = { 1, 1, 1 };
  if(loadFromRenderedText(text,textColor)){
  render((screenwidth - mWidth)/2,(screenheight - mHeight)/2);
  }
}

void TextRenderer::setBlendMode(SDL_BlendMode blending)
{
  //Set blending function
  SDL_SetTextureBlendMode( mTexture, blending );
}
void TextRenderer::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  //Modulate texture rgb
  SDL_SetTextureColorMod( mTexture, red, green, blue );
}

TextRenderer::~TextRenderer()
{
  free();
  TTF_Quit();
}

