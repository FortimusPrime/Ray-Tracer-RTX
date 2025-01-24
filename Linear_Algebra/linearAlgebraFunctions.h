#include "Vector3D.h"
#include "Matrix3D.h"
#include <random>
#include <cmath>
#include <array>
using namespace std;

// Return the cross product of two Vector3D items. 
Vector3D getCrossProduct(Vector3D a, Vector3D b);

// Generate random number between min and max.
double generateRandomNumber(double min, double max);

// Limit the color imputs in vector within 0 and 255.
Vector3D ColorMax(Vector3D color);

// Limit the color imputs in vector within 0 and 255.
array<Vector3D, 360> circleCoordinates();

double degreesToRadians(double deg);

Matrix3D getRotationMatrix(double angleA, double angleB, double angleR);