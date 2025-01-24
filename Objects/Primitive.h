#pragma once
#include <iostream>
#include <string>
#include "../Linear_Algebra/linearAlgebraFunctions.h"
#include "../Linear_Algebra/Vector3D.h"
using namespace std;

class Primitive {
public: 
    // Simple Constructor. This sets everything to 0. 
    Primitive();

    // Common Attributes
    Vector3D color;
    int specular;
    double reflective;
    string objectType;

    // Sphere Attributes
    double radius;
    Vector3D center;

    // Triangle Attributes
    Vector3D pointA;
    Vector3D pointB;
    Vector3D pointC;
    Vector3D normal;

    // Constructor for Sphere
    Primitive(Vector3D center, double radius, Vector3D color, int specular, double reflective);

    // Constructor for Triangle
    Primitive(Vector3D color, Vector3D pointA, Vector3D pointB, Vector3D pointC, int specular, double reflective );

    // Common Getters
    // Color Getter
    Vector3D getColor();

    // Specular Getter
    int getSpecular();

    // Reflective Getter
    double getReflective();

    // Type Getter. This returns the type of primitive. 
    string getType();


    // Sphere getters
    // getCenter returns the center of the sphere. 
    Vector3D getCenter();

    // getRadius returns the radius of the sphere. 
    double getRadius();

    // Triangle getters
    // getPoint returns one point of the triangle
    Vector3D getPointA();

    Vector3D getPointB();

    Vector3D getPointC();
    
    Vector3D getNormal();
};
