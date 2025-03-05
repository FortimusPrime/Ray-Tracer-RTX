#ifndef LINEARALGEBRAFUNCTIONS_H
#define LINEARALGEBRAFUNCTIONS_H

#include <array>
#include <cmath>
#include <random>

#include "Matrix3D.h"
#include "Vector3D.h"
using namespace std;

Vector3D getCrossProduct(Vector3D a, Vector3D b);
double generateRandomNumber(double min, double max);
Vector3D ColorMax(Vector3D color);
array<Vector3D, 360> circleCoordinates();
double degreesToRadians(double deg);
Matrix3D getRotationMatrix(double angleA, double angleB, double angleR);

#endif  // LINEARALGEBRAFUNCTIONS_H