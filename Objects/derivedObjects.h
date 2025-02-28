#ifndef DERIVEOBJECTS_H
#define DERIVEOBJECTS_H
#include <array>

#include "../Linear_Algebra/Matrix3D.h"
#include "../Linear_Algebra/Vector3D.h"
#include "Primitive.h"

array<Primitive, 4> buildTetrahedron(Vector3D color, Vector3D pointA, Vector3D pointB, Vector3D pointC, Vector3D pointD, int specular, double reflective);

array<Primitive, 4> buildTetrahedron2(Vector3D color, Vector3D center, double width, int specular, double reflective, double angleInput);

array<Primitive, 12> buildCube(Vector3D center, double width, Vector3D color, double angleInput);

#endif  // DERIVEOBJECTS_H