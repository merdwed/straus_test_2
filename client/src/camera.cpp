#include "camera.h"
Camera::Camera(){
    this->look_vector.x = 1;
    this->look_vector.y = 0;
    this->look_vector.z = 0;
    
    this->rotation.x = 0;
    this->rotation.y = 0;
    this->rotation.z = 0;
    this->update_look_vector();
}
    
Camera::Camera(Point3D pos): Camera(){
    this->position = pos;
}
Camera::Camera(Point3D pos, EulerAngle3D rotate_vec): Camera(pos){
    this->rotation = rotate_vec; 
    this->update_look_vector();
}
void Camera::move_to(Point3D position){
    this->position = position;
}
void Camera::move_along(Vector3D direction){
    this->position += direction.normalized() * this->speed;
}
void Camera::move_forward(){
    this->move_along(this->look_vector);
}
void Camera::move_back(){
    this->move_along(-(this->look_vector));
}
void Camera::move_left(){
    this->move_along(Vector3D(-this->look_vector.y, this->look_vector.x, 0));
}
void Camera::move_right(){
    this->move_along(Vector3D(this->look_vector.y, -this->look_vector.x, 0));
}
void Camera::check_rotate_limits(){
    if (this->rotation.x >  1.57f) this->rotation.x = 1.57f;
    if (this->rotation.x < -1.57f) this->rotation.x = -1.57f;
    if (this->rotation.z >  3.14f) this->rotation.z -= 6.28f;
    if (this->rotation.z < -3.14f) this->rotation.z += 6.28f;
}
void Camera::update_look_vector(){
    this->look_vector.y = -cos(this->rotation.x) * cos(this->rotation.z);
    this->look_vector.z = sin(this->rotation.x);
    this->look_vector.x = cos(this->rotation.x) * sin(this->rotation.z);
}
void Camera::rotate_to(EulerAngle3D rotation){
    this->rotation = rotation;
    this->check_rotate_limits();
    this->update_look_vector();
}
void Camera::rotate(EulerAngle3D rotation){
    this->rotation += rotation;
    this->check_rotate_limits();
    this->update_look_vector();
}
void Camera::rotate_left(){
    this->rotate(EulerAngle3D(0.f, 0.f, this->rotate_speed));
}
void Camera::rotate_right(){
    this->rotate(EulerAngle3D(0.f, 0.f, -(this->rotate_speed)));
}
void Camera::rotate_up(){
    this->rotate(EulerAngle3D(this->rotate_speed, 0.f, 0.f));
}
void Camera::rotate_down(){
    this->rotate(EulerAngle3D(-(this->rotate_speed), 0.f, 0.f));
}