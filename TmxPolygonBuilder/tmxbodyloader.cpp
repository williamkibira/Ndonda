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


#include "tmxbodyloader.h"

TmxBodyLoader::TmxBodyLoader(std::string filename,b2World* world)
{ this->world = world;
  Tmx::Map *map = new Tmx::Map();
  map->ParseFile(filename.c_str());
  if (map->HasError()) {
		std::cout<<"error code:"<< map->GetErrorCode()<<std::endl;
		std::cout<<"error text:"<< map->GetErrorText()<<std::endl;
		exit(0);
	
	}
         screenWidth = map->GetWidth()*map->GetTileWidth();
	 screenHeight = map->GetHeight()*map->GetTileHeight();
	 convert = new ConvertUtililty(screenHeight,screenWidth);
	 //screenHeight = 600;
	 //screenWidth = 1000;
	for(int i = 0; i < map->GetNumObjectGroups();++i)
	{
	  std::cout<<"Object Group"<<i<<std::endl;
	  const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);
	  // Iterate through all objects in the object group.
	     objectGroupResolver(objectGroup);
		
	}
	
}

int TmxBodyLoader::getScreenHeight()
{
 return screenHeight;
}
int TmxBodyLoader::getScreenWidth()
{
 return screenWidth;
}




void TmxBodyLoader::objectGroupResolver(const Tmx::ObjectGroup* objectGroup)
{		printf("INSIDE OBJ RESOLVER\n");
    for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
			// Get an object.
			const Tmx::Object *object = objectGroup->GetObject(j);
		printf("INSIDE OBJECT GRABBER\n");
			// Print information about the object.
			printf("Object Name: %s\n", object->GetName().c_str());
			printf("Object Type: %s\n", object->GetType().c_str());
			
			printf("Object Position: (%03d, %03d)\n", object->GetX(), object->GetY());
			printf("Object Size: (%03d, %03d)\n", object->GetWidth(), object->GetHeight());
	                
			 b2Vec2 objPT = convert->convertObjectPointToGamePoint(object->GetX(),object->GetY());
			const Tmx::Polygon *polygon = object->GetPolygon();
			if(polygon != 0){
			
			  printf("BEFORE CREATING OBJECTS\n");
			StaticBody *staticBody = new StaticBody(world,objPT.x,objPT.y,polygon,convert);
			DynamicBody*dynaBody = new DynamicBody(world, objPT.x,objPT.y,polygon,convert);
			  printf("AFTER CREATING OBJECTS\n");
			                staticBody->engageBody();
		                        dynaBody->engageBody();
					staticBodys.push_back(staticBody);
					dynaBodys.push_back(dynaBody);
			}
			const Tmx::Polyline *polyline = object->GetPolyline();
			if(polyline != 0){
			  printf("BEFORE MAKING POLY-LINE\n");
			  
			  /* CODE FOR MAKING POLY LINE [ WORLD TERRAIN ] */ 
			  GroundBody* groundBody = new GroundBody(world,objPT.x,objPT.y,polyline,convert);
			              groundBody->engageGround();
				      groundBodys.push_back(groundBody);
			  printf("AFTER MAKING POLY LINE\n");
			}
		}
}

std::vector< DynamicBody* > TmxBodyLoader::getDynamicBodies()
{
    return dynaBodys;
}
std::vector< StaticBody* > TmxBodyLoader::getStaticBodies()
{
    return staticBodys;
}


TmxBodyLoader::~TmxBodyLoader()
{

}

