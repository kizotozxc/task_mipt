#include "cpp-23-24-geometry.hpp"

#include <iostream>

// блок про вектор

Vector::Vector() : coord_x_(0), coord_y_(0) {}

Vector::Vector(int axle_x, int axle_y) : coord_x_(axle_x), coord_y_(axle_y) {}

int Vector::GetX() const { return coord_x_; }

int Vector::GetY() const { return coord_y_; }

int operator*(const Vector& vec1, const Vector& vec2) {
  return vec1.GetX() * vec2.GetX() + vec1.GetY() * vec2.GetY();
}

int operator^(const Vector& vec1, const Vector& vec2) {
  return vec1.GetX() * vec2.GetY() - vec1.GetY() * vec2.GetX();
}

Vector operator+(const Vector& vec1, const Vector& vec2) {
  return Vector(vec1.GetX() + vec2.GetX(), vec1.GetY() + vec2.GetY());
}  // можно через +=

Vector& Vector::operator+=(const Vector& vec) {
  coord_x_ += vec.coord_x_;
  coord_y_ += vec.coord_y_;
  return *this;
}

Vector operator-(const Vector& vec1, const Vector& vec2) {
  return Vector(vec1.GetX() - vec2.GetX(), vec1.GetY() + vec2.GetY());
}  // можно через -= или наоборот

Vector& Vector::operator-=(const Vector& vec) {
  coord_x_ -= vec.coord_x_;
  coord_y_ -= vec.coord_y_;
  return *this;
}

Vector operator*(const int& times, const Vector& vec) {
  return Vector(vec.GetX() * times, vec.GetY() * times);
}

Vector& Vector::operator*=(const int& times) {
  coord_x_ *= times;
  coord_y_ *= times;
  return *this;
}
Vector operator-(const Vector& vec) { return Vector(-vec.GetX(), -vec.GetY()); }

Vector operator*(const Vector& vec, const int& times) { return vec * times; }

Vector& operator*=(const int& times, Vector& vec) {
  vec *= times;
  return vec;
}

// блок про точку

Point::Point(int axle_x, int axle_y) : coord_x_(axle_x), coord_y_(axle_y) {}

int Point::GetX() const { return coord_x_; }

int Point::GetY() const { return coord_y_; }

void Point::Move(const Vector& vec) {
  coord_x_ += vec.GetX();
  coord_y_ += vec.GetY();
}

bool Point::ContainsPoint(const Point& pnt) const {
  return coord_x_ == pnt.GetX() && coord_y_ == pnt.GetY();
}

bool Point::CrossSegment(const Segment& seg) const {
  return seg.ContainsPoint(*this);
}

IShape* Point::Clone() const { return new Point(*this); }

Vector operator-(const Point& pnt1, const Point& pnt2) {
  return Vector(pnt1.GetX() - pnt2.GetX(), pnt1.GetY() - pnt2.GetY());
}

// блок про линию

Line::Line(Point frst_pnt, Point sec_pnt)
    : frst_pnt_(frst_pnt), sec_pnt_(sec_pnt) {}

int Line::GetA() const { return frst_pnt_.GetY() - sec_pnt_.GetY(); }

int Line::GetB() const { return sec_pnt_.GetX() - frst_pnt_.GetX(); }

int Line::GetC() const {
  return frst_pnt_.GetX() * sec_pnt_.GetY() -
         frst_pnt_.GetY() * sec_pnt_.GetX();
}

void Line::Move(const Vector& vec) {
  frst_pnt_.Move(vec);
  sec_pnt_.Move(vec);
}

bool Line::ContainsPoint(const Point& pnt) const {
  return (pnt.GetX() * GetA() + pnt.GetY() * GetB() + GetC() == 0);
}

IShape* Line::Clone() const { return new Line(*this); }

bool Line::CrossSegment(const Segment& seg) const {
  long long int dist(
      (GetA() * seg.GetA().GetX() + GetB() * seg.GetA().GetY() + GetC()) *
      (GetA() * seg.GetB().GetX() + GetB() * seg.GetB().GetY() + GetC()));
  return dist <= 0;
}

// блок про луч

Ray::Ray(Point frst_pnt, Point sec_pnt)
    : pnt_(frst_pnt),
      vec_(sec_pnt.GetX() - frst_pnt.GetX(), sec_pnt.GetY() - frst_pnt.GetY()) {
}

Vector Ray::GetVector() const { return vec_; }

Point Ray::GetA() const { return pnt_; }

void Ray::Move(const Vector& vec) { pnt_.Move(vec); }

bool Ray::ContainsPoint(const Point& pnt) const {
  Point sec_pnt(pnt_.GetX() + vec_.GetX(), pnt_.GetY() + vec_.GetY());
  Line tmp(pnt_, sec_pnt);
  return tmp.ContainsPoint(pnt) && ((vec_ * (pnt - pnt_)) >= 0);
}

bool Ray::CrossSegment(const Segment& seg) const {
  Point sec_pnt(pnt_.GetX() + vec_.GetX(), pnt_.GetY() + vec_.GetY());
  Line ray_line(pnt_, sec_pnt);
  if (!ray_line.CrossSegment(seg)) {
    return false;
  }
  Line seg_line(seg.GetA(), seg.GetB());
  long long int dist1 = seg_line.GetA() * pnt_.GetX() +
                        seg_line.GetB() * pnt_.GetY() + seg_line.GetC();
  long long int dist2 = seg_line.GetA() * (pnt_.GetX() + vec_.GetX()) +
                        seg_line.GetB() * (pnt_.GetY() + vec_.GetY()) +
                        seg_line.GetC();
  if (dist1 * dist2 <= 0) {
    return true;
  }
  return (dist1 * dist1 - dist2 * dist2 >= 0);
}

IShape* Ray::Clone() const { return new Ray(*this); }

// блок про отрезок

Segment::Segment(Point frst_pnt, Point sec_pnt)
    : frst_pnt_(frst_pnt), sec_pnt_(sec_pnt) {}

Point Segment::GetA() const { return frst_pnt_; }

Point Segment::GetB() const { return sec_pnt_; }

void Segment::Move(const Vector& vec) {
  frst_pnt_.Move(vec);
  sec_pnt_.Move(vec);
}

bool Segment::ContainsPoint(const Point& pnt) const {
  if ((frst_pnt_.GetX() == sec_pnt_.GetX()) &&
      (frst_pnt_.GetY() == sec_pnt_.GetY())) {
    return frst_pnt_.GetX() == pnt.GetX();
  }
  Ray right(frst_pnt_, sec_pnt_);
  Ray left(sec_pnt_, frst_pnt_);
  return right.ContainsPoint(pnt) && left.ContainsPoint(pnt);
}

bool Segment::CrossSegment(const Segment& seg) const {
  bool is_pnt1 = ((seg.GetA().GetX() == seg.GetB().GetX()) &&
                  (seg.GetA().GetY() == seg.GetB().GetY()));
  bool is_pnt2 = ((frst_pnt_.GetX() == sec_pnt_.GetX()) &&
                  (frst_pnt_.GetY() == sec_pnt_.GetY()));
  if (is_pnt1 && is_pnt2) {
    return frst_pnt_.GetX() == seg.GetA().GetX();
  }
  if (is_pnt1) {
    return ContainsPoint(seg.GetA());
  }
  if (is_pnt2) {
    return seg.ContainsPoint(frst_pnt_);
  }
  Ray right1(frst_pnt_, sec_pnt_);
  Ray left1(sec_pnt_, frst_pnt_);
  if (!(right1.CrossSegment(seg) && left1.CrossSegment(seg))) {
    return false;
  }
  Line tmp1(frst_pnt_, sec_pnt_);
  Line tmp2(seg.GetA(), seg.GetB());
  if ((tmp1.ContainsPoint(seg.GetA()) && tmp1.ContainsPoint(seg.GetB())) ||
      (tmp2.ContainsPoint(frst_pnt_) && tmp2.ContainsPoint(sec_pnt_))) {
    return ContainsPoint(seg.GetA()) || ContainsPoint(seg.GetB()) ||
           seg.ContainsPoint(frst_pnt_) || seg.ContainsPoint(sec_pnt_);
  }
  return true;
}

IShape* Segment::Clone() const { return new Segment(*this); }

// блок про круг

Circle::Circle(Point centre, size_t rad) : rad_(rad), centre_(centre) {}

Point Circle::GetCentre() const { return centre_; }

size_t Circle::GetRadius() const { return rad_; }

void Circle::Move(const Vector& vec) { centre_.Move(vec); }

bool Circle::ContainsPoint(const Point& pnt) const {
  return ((pnt.GetX() - centre_.GetX()) * (pnt.GetX() - centre_.GetX()) +
          (pnt.GetY() - centre_.GetY()) * (pnt.GetY() - centre_.GetY())) <=
         static_cast<int>(rad_ * rad_);
}

bool Circle::CrossSegment(const Segment& seg) const {
  if (ContainsPoint(seg.GetA()) xor ContainsPoint(seg.GetB())) {
    return true;
  }
  if (((seg.GetA().GetX() - centre_.GetX()) *
           (seg.GetA().GetX() - centre_.GetX()) +
       (seg.GetA().GetY() - centre_.GetY()) *
           (seg.GetA().GetY() - centre_.GetY())) ==
          static_cast<int>(rad_ * rad_) ||
      ((seg.GetB().GetX() - centre_.GetX()) *
           (seg.GetB().GetX() - centre_.GetX()) +
       (seg.GetB().GetY() - centre_.GetY()) *
           (seg.GetB().GetY() - centre_.GetY())) ==
          static_cast<int>(rad_ * rad_)) {
    return true;
  }
  if (ContainsPoint(seg.GetA())) {
    return false;
  }
  Line tmp(seg.GetA(), seg.GetB());
  long long int dist =
      (tmp.GetA() * centre_.GetX() + tmp.GetB() * centre_.GetY() + tmp.GetC());
  long long int distsqv = dist * dist;
  long long int rad = static_cast<long long int>(rad_ * rad_) *
                      (tmp.GetA() * tmp.GetA() + tmp.GetB() * tmp.GetB());
  return distsqv <= rad;
  // if (distsqv > rad) {
  //   return false;
  // }
  // return ((seg.GetA() - seg.GetB()) * (Centre_ - seg.GetB()) > 0) &&
  //        ((seg.GetB() - seg.GetA()) * (Centre_ - seg.GetA()) > 0);
}

IShape* Circle::Clone() const { return new Circle(*this); }
