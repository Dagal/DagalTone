#include "vector2D.hpp"

#include <cmath>

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

Vector2D Vector2D::unitVector() const
{
  Vector2D ret;
  if ((mx != 0) && (my != 0))
    {
      ret = *this / norm();
    }
  return ret;
}

double Vector2D::norm() const
{
  double ret;
  if ((mx != 0) && (my != 0))
    {
      ret = sqrt(mx * mx + my * my);
    }
  return ret;
}

void Vector2D::invert()
{
  mx = -mx;
  my = -my;
}

Vector2D operator-(const Vector2D& v)
{
  Vector2D ret(v);
  ret.invert();
  return ret;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
  Vector2D ret(v1);
  ret += v2;
  return ret;
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
  Vector2D ret(v1);
  ret -= v2;
  return ret;
}

Vector2D operator*(const Vector2D& v1, const double s)
{
  Vector2D ret(v1);
  ret *= s;
  return ret;
}

Vector2D operator/(const Vector2D& v1, const double s)
{
  Vector2D ret(v1);
  ret /= s;
  return ret;
}
