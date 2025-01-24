// Vector3D.h
#pragma once
#include <iostream>
#include <cmath> 
using namespace std;

class Vector3D {
public:
    // Attributes (public for simplicity)
    double x, y, z;

    // Constructor
    Vector3D(double x = 0, double y = 0, double z = 0);

    // Overloads
    Vector3D operator + (const Vector3D& other) const;
    Vector3D operator - (const Vector3D& other) const;
    Vector3D operator * (double scalar) const;
    Vector3D operator / (double scalar) const;
    double operator * (const Vector3D& other) const;
    bool operator == (const Vector3D& other) const;

    // Magnitude of the vector
    double magnitude() const;

    // Normalize the vector
    Vector3D normalize() const;

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Print the vector (for debugging)
    void print() const;
};

