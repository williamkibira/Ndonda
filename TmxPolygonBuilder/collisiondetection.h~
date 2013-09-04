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
/*****************************************************************************************/
/*THIS WILL DETECT WHICH TWO BODIES ARE IN CONTACT IN THE SIMULATION AND CHECK THEIR ID S*/
/*THIS WAY A CONFORMING ACTION / REACTION CAN BE TAKEN IN REPSONSE TO THAT ACTION BEFORE */
/* DURING AND AFTER CONTACT HAS BEEN MADE WITH THE BODIES SPECIFIC INTEREST IS IN THE    */
/*IMPULSE OF THE BODIES AFTER COLLISION AND ALSO IF THE BODIES HAVE HAD A HUGE COLLISON  */
/*****************************************************************************************/

#include <Box2D/Box2D.h>
#include "BodyTypes.h"
#include "body.h"
#include "dynamicbody.h"


#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

class CollisionDetection : public b2ContactListener
{

public:
    CollisionDetection();
  void BeginContact(b2Contact* contact);
  void EndContact(b2Contact* contact);
  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  
    virtual ~CollisionDetection();
private:
  
  int Body_ID;
  int Body_type;
  //State* state;
  void* bodyA;
  void* bodyB;
};

#endif // COLLISIONDETECTION_H
