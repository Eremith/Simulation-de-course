class Point3D {
private:
    int x, y, z;
public:
    Point3D(const int& newx, const int& newy, const int& newz);
    int GetX();
    int GetY();
    int GetZ();
    float distanceTo(const Point3D& otherPoint3D);
};