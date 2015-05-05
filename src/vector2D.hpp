#ifndef _VECTOR2D_HPP_
#define _VECTOR2D_HPP_

class Vector2D
{
public:
  Vector2D();
  Vector2D(const double x, const double y);
  Vector2D(const Vector2D& v);
  virtual ~Vector2D();

  Vector2D& operator=(const Vector2D& v);
  Vector2D& operator+=(const Vector2D& v);
  Vector2D& operator-=(const Vector2D& v);
  Vector2D& operator*=(const double s);
  Vector2D& operator/=(const double s);

  double getX() const;
  double getY() const;

  void setX(const double x);
  void setY(const double y);
  void set(const double x, const double y);

  
protected:

private:
  double mx,my;
};

Vector2D operator+(Vector2D& v1, Vector2D& v2);
Vector2D operator-(Vector2D& v1, Vector2D& v2);
Vector2D operator*(Vector2D& v1, double s);
Vector2D operator/(Vector2D& v1, double s);

#endif // _VECTOR2D_HPP_
