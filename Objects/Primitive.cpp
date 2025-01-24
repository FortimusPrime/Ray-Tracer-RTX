#include "Primitive.h"

    Primitive::Primitive() {
        // Default for Sphere attributes
        this->color = Vector3D(0, 0, 0);
        this->radius = 0;
        this->center = Vector3D(0, 0, 0);
        this->specular = 0;
        this->reflective = 0.0;
        this->objectType = "primitive";  // Can set to "primitive" as default

        // Default for Triangle attributes
        this->pointA = Vector3D(0, 0, 0);
        this->pointB = Vector3D(0, 0, 0);
        this->pointC = Vector3D(0, 0, 0);
        this->normal = Vector3D(0, 0, 0);  // Defaults to a zero vector
    }

    // Constructor for Sphere
    Primitive::Primitive(Vector3D center, double radius, Vector3D color, int specular, double reflective){
        this->color = color;
        this->radius = radius;
        this->center = center;
        this->specular = specular;
        this->reflective = reflective;
        this->objectType = "sphere";

        this->normal = Vector3D(0, 0, 0);
        this->pointA = Vector3D(0, 0, 0);
        this->pointB = Vector3D(0, 0, 0);
        this->pointC = Vector3D(0, 0, 0);
    }

    // Constructor for Triangle
    Primitive::Primitive(Vector3D color, Vector3D pointA, Vector3D pointB, Vector3D pointC, int specular, double reflective ){
        this->color = color;
        this->pointA = pointA;
        this->pointB = pointB;
        this->pointC = pointC;
        this->specular = specular;
        this->reflective = reflective;
        this->normal = getCrossProduct(pointC-pointA, pointB-pointA);
        this->objectType = "triangle";
        
        this->radius = 0.0;
        this->center = Vector3D(0, 0, 0);
    }

    // Common Getters
    Vector3D Primitive::getColor(){
        return this->color;
    }
    int Primitive::getSpecular(){
        return this->specular;
    }
    double Primitive::getReflective(){
        return this->reflective;
    }
    string Primitive::getType(){
        return this->objectType;
    }

    // Sphere getters
    Vector3D Primitive::getCenter(){
        return this->center;
    }

    double Primitive::getRadius(){
        return this->radius;
    }

    // Triangle getters
    Vector3D Primitive::getPointA(){
        return this->pointA;
    }

    Vector3D Primitive::getPointB(){
        return this->pointB;
    }

    Vector3D Primitive::getPointC(){
        return this->pointC;
    }
    
    Vector3D Primitive::getNormal(){
        return this->normal;
    }