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
  mx = v.getX();
  my = v.getY();
}

Vector2D::~Vector2D()
{
}

double Vector2D::getX()
{
  return mx;
}

double Vector2D::getY()
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


  
