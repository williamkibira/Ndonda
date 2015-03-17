#include "../datatypes/vector2d.h"

#ifndef COLLISION_RESULT_H
#define COLLISION_RESULT_H
struct CollisionResult{
  
  bool toIntersect;
  bool Intersected;
  
  Vector2D* MinTranslationVector;
};

#endif // COLLISION_RESULT_H