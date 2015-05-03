#include "vector2D.hpp"

Vector2D::Vector2D()
{
  mx = 0.0;
  my = 0.0;
}

Vector2D::Vector2D(const double x, const double y)
{
  mx = x;
  my = y;
}

Vector2D::Vector2D(const Vector2D& v)
{
  mx = v.mx;
  my = v.mx;
}

Vector2D::~Vector2D()
{
}

Vector2D& Vector2D::operator=(const Vector2D& v)
{
  if(&v != this)
    {
      mx = v.mx;
      my = v.my;
    }
  return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
  mx += v.mx;
  my += v.my;
  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
  mx -= v.mx;
  my -= v.my;
  return *this;
}

Vector2D& Vector2D::operator*=(const double s)
{
  mx *= s;
  my *= s;
  return *this;
}

Vector2D& Vector2D::operator/=(const double s)
{
  mx /= s;
  my /= s;
  return *this;
}

double Vector2D::getX() const
{
  return mx;
}

double Vector2D::getY() const
{
  return my;
}

void Vector2D::setX(const double x)
{
  mx = x;
}

void Vector2D::setY(const double y)
{
  my = y;
}

void Vector2D::set(const double x, const double y)
{
  mx = x;
  my = y;
}


  
