#include "structs.h"

xyz::xyz(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
xyz::xyz(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
xyz xyz::operator+(xyz& rhs) {
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z}; 
}
xyz xyz::operator-(xyz& rhs) {
    return {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z}; 
}
xyz xyz::operator-() {
    return {-this->x, -this->y, -this->z}; 
}

xyz& xyz::operator+=(const xyz& rhs) {                           
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this; 
}
xyz& xyz::operator-=(const xyz& rhs){
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this; 
}


Point3D::Point3D():xyz(){}
Point3D::Point3D(float x, float y, float z):xyz(x,y,z){}
Point3D Point3D::operator+(xyz& rhs) {
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z}; 
}
Point3D Point3D::operator-(xyz& rhs) {
    return {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z}; 
}
Point3D Point3D::operator-() {
    return {-this->x, -this->y, -this->z}; 
}
    

Vector3D::Vector3D():xyz(){}
Vector3D::Vector3D(float x, float y, float z):xyz(x,y,z){}
float Vector3D::length(){
    return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}
Vector3D Vector3D::normalized(){
    float d = this->length();
    if(d == 0)
        return *this;
    if(fabs(d - 1.0) < std::numeric_limits<double>::epsilon()){
        return *this;
    }
    return {this->x /= d, this->y /= d, this->z /= d};
}
Vector3D Vector3D::operator+(xyz& rhs) {
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z}; 
}
Vector3D Vector3D::operator-(xyz& rhs) {
    return {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z}; 
}
Vector3D Vector3D::operator-() {
    return {-this->x, -this->y, -this->z}; 
}
Vector3D& Vector3D::operator*=(const float& rhs){
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this; 
}
Vector3D Vector3D::operator*(const float& rhs) {                           
    return {this->x * rhs, this->y * rhs, this->z * rhs}; 
}


EulerAngle3D::EulerAngle3D():xyz(){}
EulerAngle3D::EulerAngle3D(float x, float y, float z):xyz(x,y,z){}
EulerAngle3D EulerAngle3D::operator+(xyz& rhs) {
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z}; 
}
EulerAngle3D EulerAngle3D::operator-(xyz& rhs) {
    return {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z}; 
}
EulerAngle3D EulerAngle3D::operator-() {
    return {-this->x, -this->y, -this->z}; 
}
