/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#define _USE_MATH_DEFINES
#define TO_DEGREES 180/M_PI

template <class T> class Vector2D;
typedef Vector2D<int> Vector2Di;
typedef Vector2D<float> Vector2Df;
typedef Vector2D<long> Vector2Dl;

template <class T>
class Vector2D
{

public:
    Vector2D();
    virtual ~Vector2D();
    Vector2D(const T  new_x, const T new_y);
    Vector2D(const Vector2D< T >& otherVector);
    
    Vector2D<T>& set(T new_x, T new_y);
    Vector2D<T>& set(const Vector2D<T>& otherVector);
    
    Vector2D<T>& operator +=(const Vector2D<T>& otherVector);
    Vector2D<T>& operator -=(const Vector2D<T>& otherVector);
    Vector2D<T>& operator *=(T aScalar);
    Vector2D<T>& operator /=(T aScalar);
    
    Vector2D<T> operator+(const Vector2D<T>& otherVector) const;
    Vector2D<T> operator-(const Vector2D<T>& otherVector) const;
    Vector2D<T> operator-(void) const;
    Vector2D<T> operator*(T aScalar) const;
    Vector2D<T> operator/(T aScalar) const;
    
    Vector2D<T>& add(T add_x, T add_y);
    Vector2D<T>& add(const Vector2D<T>& otherVector);
    Vector2D<T>& sub(T sub_x, T sub_y);
    Vector2D<T>& sub(const Vector2D& otherVector);
    Vector2D<T>& mul(T aScalar);
    Vector2D<T>& div(T aScalar);
    Vector2D<T>& invert();
    void reflect();
    bool operator==(const Vector2D<T>& otherVector) const;
    bool operator!=(const Vector2D<T>& otherVector) const;
    
    T dot(const Vector2D<T>& otherVector) const;
    static Vector2D<T>& cross(const Vector2D<T>& otherVectorU, const Vector2D<T>& otherVectorV);
    T perpdot(const Vector2D<T>& otherVector) const;
    
    void normalize();
    Vector2D<T> normalized() const;
    
    float lengthSquared() const;
    float length() const;
    
    float angleDeg();
    float angleRad();
    
    Vector2D<T>& rotate(float aAngleRad);
    Vector2D<T> lerp( T t, const Vector2D& otherVector) const;
    
    T x;
    T y;
    
    
};

#endif // VECTOR2D_H
