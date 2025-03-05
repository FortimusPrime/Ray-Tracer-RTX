#ifndef RAYTRACINGFUNCTIONS_H
#define RAYTRACINGFUNCTIONS_H

#include <array>

#include "../Linear_Algebra/Vector3D.h"
#include "../Objects/Camera.h"
#include "../Objects/Light.h"
#include "../Objects/Primitive.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"

#define INF 2147483647
#define RECURSION_DEPTH 5

Vector3D reflectRay(Vector3D R, Vector3D N);
bool pointInTriangle(const Vector3D& P, Primitive triangle);
array<double, 2> IntersectRayTriangle(Vector3D O, Vector3D D, Primitive triangle);
array<double, 2> IntersectRaySphere(Vector3D O, Vector3D D, Primitive sphere);
array<double, 2> ClosestIntersection(Vector3D cameraOrigin, Vector3D D, double t_min, double t_max, Scene scene);
double ComputeLighting(Vector3D P, Vector3D N, Vector3D V, int s, Scene scene);
Vector3D TraceRay(Vector3D cameraOrigin, Vector3D D, double t_min, int t_max, int recursion_depth, Scene& scene);
Vector3D CanvasToViewport(double x, double y, Camera& camera);
vector<vector<string>> render(Scene& scene, Camera& camera);

#endif  // RAYTRACINGFUNCTIONS_H