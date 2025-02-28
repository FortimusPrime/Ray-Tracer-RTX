#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include <time.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Linear_Algebra/Vector3D.h"
#include "../Objects/Light.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"

using namespace std;

struct ColorPalette {
  static const Vector3D red;
  static const Vector3D blue;
  static const Vector3D green;
  static const Vector3D yellow;
  static const Vector3D cyan;
  static const Vector3D magenta;
  static const Vector3D orange;
  static const Vector3D purple;
  static const Vector3D pink;
  static const Vector3D brown;
  static const Vector3D gray;
  static const Vector3D white;
};

timespec getTime();
double calculateElapsedTime(timespec start_time);
void map2DtoFile(int CanvasWidth, int CanvasHeight, ofstream& ppmFile, vector<vector<string>>& map2D);
Scene makeScene(Vector3D coords1, Vector3D coords2, Vector3D coords3, Vector3D BACKGROUND_COLOR, double angleInput);

#endif  // MISCFUNCTIONS_H