#pragma once
#include "structs.h"
class Camera{
public:
    Point3D position; //position of camera
    Vector3D look_vector; //direction that camera look
    EulerAngle3D rotation;  //euler angles rotation from (0,-1,0) 
    float speed = 0.2f; //distance which camera move per tick
    float rotate_speed = 0.025f; //angle which camera rotate per one tick
    Camera();
    Camera(Point3D pos);
    Camera(Point3D pos, EulerAngle3D rotate_vec);
    void move_to(Point3D position);
    void move_along(Vector3D direction);
    void move_forward();
    void move_back();
    void move_left();
    void move_right();
private:
    void check_rotate_limits();
    void update_look_vector();
public:
    void rotate_to(EulerAngle3D rotation);
    void rotate(EulerAngle3D rotation);
    void rotate_left();
    void rotate_right();
    void rotate_up();
    void rotate_down();
};