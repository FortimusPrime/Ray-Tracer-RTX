#pragma once
#include "Vector3D.h"
#include <iostream>
#include <cmath> 
using namespace std;

class Matrix3D {
public:
    // Attributes (public for simplicity)
    Vector3D colX, colY, colZ;

    // Constructor
    Matrix3D(Vector3D colX = Vector3D(0, 0, 0), Vector3D colY = Vector3D(0, 0, 0), Vector3D colZ = Vector3D(0, 0, 0));


    // Overloads
    Vector3D operator * (Vector3D vector) const;

    // Getters
    // Rows
    Vector3D getRow0() const;
    Vector3D getRow1() const;
    Vector3D getRow2() const;

    // Columns
    Vector3D getCol0() const;
    Vector3D getCol1() const;
    Vector3D getCol2() const;

    // First Row
    double getX0() const;
    double getX1() const;
    double getX2() const;

    // Second Row
    double getY0() const;
    double getY1() const;
    double getY2() const;

    // Third Row
    double getZ0() const;
    double getZ1() const;
    double getZ2() const;

    Matrix3D rotationMatrix(double angleAlpha, double angleBeta, double anglePhi) const;

    // Print the vector (for debugging)
    void print() const;
};

