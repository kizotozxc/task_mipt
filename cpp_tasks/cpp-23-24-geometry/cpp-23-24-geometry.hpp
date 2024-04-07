#pragma once
#include <iostream>

class Vector {
 public:
  Vector();
  Vector(int axle_x, int axle_y);
  int GetX() const;
  int GetY() const;
  Vector& operator+=(const Vector& vec);
  Vector& operator-=(const Vector& vec);
  Vector& operator*=(const int& times);

 private:
  int coord_x_;
  int coord_y_;
};

class Point;
class Segment;

struct IShape {
 public:
  virtual void Move(const Vector& vec) = 0;
  virtual bool ContainsPoint(const Point& pnt) const = 0;
  virtual bool CrossSegment(const Segment& seg) const = 0;
  virtual IShape* Clone() const = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  int GetX() const;
  int GetY() const;
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& pnt) const override;
  bool CrossSegment(const Segment& seg) const override;
  IShape* Clone() const override;
  Point(int axle_x, int axle_y);

 private:
  int coord_x_;
  int coord_y_;
};

class Line : public IShape {
 public:
  int GetA() const;
  int GetB() const;
  int GetC() const;
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& pnt) const override;
  bool CrossSegment(const Segment& seg) const override;
  IShape* Clone() const override;
  Line(Point frst_pnt, Point sec_pnt);

 private:
  Point frst_pnt_;
  Point sec_pnt_;
};

class Ray : public IShape {
 public:
  Ray(Point frst_pnt, Point sec_pnt);
  Vector GetVector() const;
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& pnt) const override;
  bool CrossSegment(const Segment& seg) const override;
  IShape* Clone() const override;
  Point GetA() const;

 private:
  Vector vec_;
  Point pnt_;
};

class Segment : public IShape {
 public:
  Point GetA() const;
  Point GetB() const;
  Segment(Point frst_pnt, Point sec_pnt);
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& pnt) const override;
  bool CrossSegment(const Segment& seg) const override;
  IShape* Clone() const override;

 private:
  Point frst_pnt_;
  Point sec_pnt_;
};

class Circle : public IShape {
 public:
  Point GetCentre() const;
  size_t GetRadius() const;
  Circle(Point centre, size_t rad);
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& pnt) const override;
  bool CrossSegment(const Segment& seg) const override;
  IShape* Clone() const override;

 private:
  size_t rad_;
  Point centre_;
};

Vector operator*(const int& times, const Vector& vec);
Vector& operator*=(const int& times, Vector& vec);
Vector operator-(const Point& pnt1, const Point& pnt2);
int operator*(const Vector& vec1, const Vector& vec2);
int operator^(const Vector& vec1, const Vector& vec2);
Vector operator+(const Vector& vec1, const Vector& vec2);
Vector operator-(const Vector& vec1, const Vector& vec2);
Vector operator-(const Vector& vec);
