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

#include "datatypes/vector2d.h"
template <class T> Vector2D< T >::Vector2D():x(0),y(0)
{}

template <class T> Vector2D< T >::Vector2D(const T new_x, const T new_y):x(new_x),y(new_y)
{}
template <class T> Vector2D< T >::Vector2D(const Vector2D< T >& otherVector)
{
  this->x = otherVector.x;
  this->y = otherVector.y;
}
template <class T> Vector2D< T >& Vector2D< T >::set(T new_x, T new_y)
{
  x = new_x;
  y = new_y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::set(const Vector2D< T >& otherVector)
{
  x = otherVector.x;
  y = otherVector.y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::add(T add_x, T add_y)
{
  x += add_x;
  y += add_y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::add(const Vector2D< T >& otherVector)
{
  x += otherVector.x;
  y += otherVector.y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::sub(T sub_x, T sub_y)
{
  x -= sub_x;
  y -= sub_y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::sub(const Vector2D& otherVector)
{
  x -= otherVector.x;
  y -= otherVector.y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::mul(T aScalar)
{
  x *= aScalar;
  y *= aScalar;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::div(T aScalar)
{
  T m = 1.0f / aScalar;
  x*= m;
  y *= m;
  return *this;
}
template <class T> float Vector2D< T >::angleRad()
{
  T angle = atan2f(x, y);
  if (angle < 0)
    angle += (2*M_PI);
  return angle;
}
template <class T> float Vector2D< T >::angleDeg()
{
  T angle = atan2(x, y) * TO_DEGREES;
  if (angle < 0)
    angle += (2*M_PI);
  return angle;
}
template <class T> Vector2D< T >& Vector2D< T >::rotate(float aAngleRad)
{
  float s = sinf(aAngleRad);
  float c = cosf(aAngleRad);
  
  T tmpx = x * c - y * s;
  T tmpy = y * s + y * c;
  
  x = tmpx; y = tmpy;
  return *this;
}
template <class T> Vector2D< T > Vector2D< T >::lerp(T t, const Vector2D& otherVector) const
{
  return Vector2D(x * (1 - t) + otherVector.x * t, y * (1 - t) + otherVector.y * t);
}
template <class T> float Vector2D< T >::length() const
{
  return sqrtf(lengthSquared());
}
template <class T> float Vector2D< T >::lengthSquared() const
{
  return y * y + x * x;
}
template <class T> Vector2D< T > Vector2D< T >::normalized() const
{
  Vector2D<T> v(*this);
  v.normalize();
  return v;
}
template <class T> void Vector2D< T >::normalize()
{
  T len = length();
  if (len != 0)
  {
    T m = 1.0f / len;
    x *= m;
    y *= m;
  }
}

template <class T> T Vector2D< T >::dot(const Vector2D< T >& otherVector) const
{
  return x * otherVector.x + y * otherVector.y;
}
template <class T> T Vector2D< T >::perpdot(const Vector2D< T >& otherVector) const
{
  return x * otherVector.y - y * otherVector.x;
} 
template <class T> bool Vector2D< T >::operator==(const Vector2D< T >& otherVector) const
{
  return (x == otherVector.x) && (y == otherVector.y);
}
template <class T> bool Vector2D< T >::operator!=(const Vector2D< T >& otherVector) const
{
  return (x != otherVector.x) || (y != otherVector.y);
}
template <class T> Vector2D< T >& Vector2D< T >::operator+=(const Vector2D< T >& otherVector)
{
  x += otherVector.x;
  y += otherVector.y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::operator-=(const Vector2D< T >& otherVector)
{
  x -= otherVector.x;
  y -= otherVector.y;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::operator/=(T aScalar)
{
  T m = 1.0f / aScalar;
  x *= m;
  y *= m;
  return *this;
}
template <class T> Vector2D< T >& Vector2D< T >::operator*=(T aScalar)
{
  x *= aScalar;
  y *= aScalar;
  return *this;
}

template <class T> Vector2D< T > Vector2D< T >::operator+(const Vector2D< T >& otherVector) const
{
  return Vector2D(x + otherVector.x, y + otherVector.y);
}
template <class T> Vector2D< T > Vector2D< T >::operator-(const Vector2D< T >& otherVector) const
{
  return Vector2D(x - otherVector.x, y - otherVector.y);
} 
template <class T> Vector2D< T > Vector2D< T >::operator-(void ) const
{
  return Vector2D(-x, -y);
}
template <class T> Vector2D< T > Vector2D< T >::operator*(T aScalar) const
{
  return Vector2D(x * aScalar, y * aScalar);
}
template <class T> Vector2D< T > Vector2D< T >::operator/(T aScalar) const
{
  T m = 1.0 / aScalar;
  return Vector2D(x * m, y * m);
}

template <class T> Vector2D< T >& Vector2D< T >::cross(const Vector2D< T >& otherVectorU, const Vector2D< T >& otherVectorV)
{
  return Vector2D( otherVectorU.x * otherVectorV.y - otherVectorU.y * otherVectorV.x,
		   otherVectorU.y * otherVectorV.x - otherVectorU.x * otherVectorV.y);
}
template <class T> Vector2D< T >& Vector2D< T >::invert()
{
   return new Vector2D< T >(-y,x);
}
void Vector2D::reflect()
{
  x *= -1;
  y *= -1;
}

template <class T> Vector2D< T >::~Vector2D()
{}




