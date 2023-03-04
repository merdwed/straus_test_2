#pragma once
#include <cmath>
#include <limits>
struct xyz{
    float x = 0;
    float y = 0;
    float z = 0;
    xyz();
    xyz(float x, float y, float z);
    xyz operator+(xyz& rhs);
    xyz operator-(xyz& rhs);
    xyz operator-();
    
    xyz& operator+=(const xyz& rhs) ;
    xyz& operator-=(const xyz& rhs);
    
};
struct Point3D: xyz{
    Point3D();
    Point3D(float x, float y, float z);
    Point3D operator+(xyz& rhs);
    Point3D operator-(xyz& rhs);
    Point3D operator-() ;
    
};
struct Vector3D: xyz{
    Vector3D();
    Vector3D(float x, float y, float z);
    float length();
    Vector3D normalized();
    Vector3D operator+(xyz& rhs);
    Vector3D operator-(xyz& rhs);
    Vector3D operator-();
    Vector3D& operator*=(const float& rhs);
    Vector3D operator*(const float& rhs);
};
struct EulerAngle3D: xyz{
    EulerAngle3D();
    EulerAngle3D(float x, float y, float z);
    EulerAngle3D operator+(xyz& rhs);
    EulerAngle3D operator-(xyz& rhs);
    EulerAngle3D operator-();
    
};