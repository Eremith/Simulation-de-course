#include <iostream>
#include <cmath>
#include "Point3D.h"

using namespace std;

Point3D::Point3D(const int& newx, const int& newy, const int& newz) : x(newx), y(newy), z(newz) {}
int Point3D::GetX() {
    return x;
}
int Point3D::GetY() {
    return y;
}
int Point3D::GetZ() {
    return z;
}
float Point3D::distanceTo(const Point3D& otherPoint3D) {
    const int dx = x - otherPoint3D.x;
    const int dy = y - otherPoint3D.y;
    const int dz = z - otherPoint3D.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}