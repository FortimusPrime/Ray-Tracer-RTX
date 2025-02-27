// To Run: clang++ -Xpreprocessor -fopenmp -lomp
// -I/opt/homebrew/Cellar/libomp/19.1.3/include
// -L/opt/homebrew/Cellar/libomp/19.1.3/lib simple_parallel.cpp -o
// parallel_example && ./parallel_example
//  clang++ -Xpreprocessor -fopenmp -lomp
//  -I/opt/homebrew/Cellar/libomp/19.1.3/include
//  -L/opt/homebrew/Cellar/libomp/19.1.3/lib simple_parallel.cpp -o
//  parallel_example && ./parallel_example
#include <time.h>

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "../Linear_Algebra/Matrix3D.h"
#include "../Linear_Algebra/Vector3D.h"
#include "../Linear_Algebra/linearAlgebraFunctions.h"
#include "../Objects/Primitive.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"
#include "../Ray-Tracing/RayTracingFunctions.h"
using namespace std;

// Global Vars
int distance_viewport_camera = 1;
int inf = 2147483647;
int recursion_depth = 0;

// Viewport Dims
int ViewportWidth = 1;
int ViewportHeight = 1;

// Canvas Dims
int CanvasWidth = 800;
int CanvasHeight = 800;

// These are the canvas coordinates in which the parallel processing will be
// mapping the color vectors to. Adjust width accordingly.
array<array<string, 800>, 800> map2D;
string colorToMap;

Vector3D red = Vector3D(255, 0, 0);
Vector3D blue = Vector3D(0, 0, 255);
Vector3D green = Vector3D(0, 255, 0);
Vector3D yellow = Vector3D(255, 255, 0);
Vector3D cyan = Vector3D(0, 255, 255);
Vector3D magenta = Vector3D(255, 0, 255);
Vector3D orange = Vector3D(255, 165, 0);
Vector3D purple = Vector3D(128, 0, 128);
Vector3D pink = Vector3D(255, 192, 203);
Vector3D brown = Vector3D(165, 42, 42);
Vector3D gray = Vector3D(128, 128, 128);
Vector3D white = Vector3D(255, 255, 255);

Vector3D BACKGROUND_COLOR = cyan;

// 0, 1, 8 is the center of the circle

Scene makeScene(Vector3D coords1, Vector3D coords2, Vector3D coords3,
                double angleInput) {
  // Create Objects
  Primitive ground_sphere =
      Primitive(Vector3D(0, -5050, 100), 5000, green, 0, 0.0);
  Primitive sphere = Primitive(coords1, 1, blue, 500, 0.3);

  array<Primitive, 4> tetra = buildTetrahedron2(Vector3D(255, 255, 0), coords3,
                                                1, 25, 0.0, angleInput);  // Tip

  vector<Primitive> objects;
  objects.push_back(ground_sphere);
  objects.push_back(sphere);

  for (int i = 0; i <= 3; i++) {
    objects.push_back(tetra[i]);
  }

  array<Primitive, 12> cube = buildCube(coords2, 0.8, red, angleInput);
  for (int i = 0; i < 12; i++) {
    objects.push_back(cube[i]);
  }

  Light light1 = Light("ambient", 0.2, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
  Light light2 = Light("point", 0.6, Vector3D(2, 1, 0), Vector3D(0, 0, 0));
  Light light3 =
      Light("directional", 0.2, Vector3D(0, 0, 0), Vector3D(1, 4, 4));
  Light light4 = Light("point", 0.6, Vector3D(2, 1, 0), Vector3D(0, 0, 0));
  Light light5 = Light("point", 0.2, Vector3D(-2, 1, 0), Vector3D(0, 0, 0));

  vector<Light> lights;
  lights.push_back(light1);
  lights.push_back(light2);
  lights.push_back(light3);
  lights.push_back(light4);
  lights.push_back(light5);

  Scene scene = Scene(objects, lights);
  return scene;
}

void render(Scene scene, Vector3D cameraOrigin) {
  cout << "Engaging render" << endl;
  // My idea:
  // We could have a tensor, that is a 2D matrix which would represent each
  // point in the canvas, and it would be assigned it's index. That way, after
  // the parallel operation, we could "paint" on the canvas

  for (int x = -CanvasWidth / 2; x < CanvasWidth / 2; x++) {
#pragma omp parallel for
    for (int y = -CanvasHeight / 2; y < CanvasHeight / 2; y++) {
      Vector3D D = CanvasToViewport(
          y, -x, ViewportWidth, ViewportHeight, CanvasWidth, CanvasHeight,
          distance_viewport_camera);  // NOTE, the second value is 0, when in
                                      // Python it's 0.5
      D = D / D.magnitude();
      Vector3D color =
          TraceRay(cameraOrigin, D, double(distance_viewport_camera), inf,
                   recursion_depth, scene, BACKGROUND_COLOR);
      color = ColorMax(color);
      // colorToMap is the temporary which will take the color and map it to the
      // map2D
      colorToMap = to_string(int(color.getX())) + " " +
                   to_string(int(color.getY())) + " " +
                   to_string(int(color.getZ())) + "   ";
      // Since values tend to go to the negatives, we add the offset to map
      // correctly to the map2D
      map2D[y + CanvasHeight / 2][x + CanvasWidth / 2] = colorToMap;
    }
  }
}

int main() {
  // Profiling time
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  double x_real = 0.0;
  double y_real = 0.0;
  double z_real = 0;

  string fileName;
  int count = 0;
  Vector3D color = Vector3D(1, 2, 3);
  array<Vector3D, 360> circle = circleCoordinates();

  int prev = -1;
  int progress = 0;
  double final_frame = 360 * 2;

  double result = 0;
  for (int frame = (360 * 2) - 1; frame < final_frame; frame++) {
    // Calculate the depth of the camera for the tracking animation
    result = 0.25 * (360.0 / (0.5 * (frame + 1)));

    if (frame < 360 || result > 0.7) {
      z_real = result;
    }

    // Vector3D cameraOrigin = Vector3D(x_real, y_real, z_real);
    Vector3D cameraOrigin = Vector3D(1, 1, 1);

    fileName = "../Output/RTX_Test/framerec" + to_string(frame) + ".ppm";
    // Write the PPM header
    ofstream ppmFile(fileName);

    ppmFile << "P3\n";  // PPM file format (plain text)
    ppmFile << CanvasWidth << " " << CanvasHeight
            << "\n";     // Image dimensions: 3 pixels wide, 2 pixels high
    ppmFile << "255\n";  // Maximum color value (8-bit)

    cout << "Making Scene" << endl;
    Scene scene =
        makeScene(circle[frame % 360], circle[((int)frame + 120) % 360],
                  circle[((int)frame + 240) % 360], frame);
    cout << "Scene made" << endl;
    render(scene, cameraOrigin);
    cout << "Scene Rendered" << endl;

    // This nested for loop maps the map2D values to the ppm file.
    for (int x = 0; x < CanvasWidth; x++) {
      for (int y = 0; y < CanvasHeight; y++) {
        ppmFile << map2D[y][x];
      }
      ppmFile << "\n";
    }

    progress = int((frame / final_frame) * 100);
    if (progress != prev) {
      cout << "Loading... " << progress << " done. Rendering frame " << frame
           << " of " << int(final_frame) << endl;
      prev = progress;
    }
  }

  // Get end time
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
  printf("Execution time: %f seconds\n", elapsed);
  cout << "DONE!!" << endl;
  return 0;
}

// int mainAUX() {
//   double x_real = 0.0;
//   double y_real = 0.0;
//   double z_real = 0;

//   string fileName;
//   int count = 0;
//   array<Vector3D, 360> circle = circleCoordinates();

//   int prev = -1;
//   int progress = 0;
//   double final_frame = 360 * 2;
//   // double final_frame = 1;

//   double result = 0;
//   for (int frame = 360; frame < final_frame; frame++) {
//     // Calculate the depth of the camera for the tracking animation
//     result = 0.25 * (360.0 / (0.5 * (frame + 1)));

//     if (frame < 360 || result > 0.7) {
//       z_real = result;
//     }

//     cout << "Camera " << z_real << endl;
//     Vector3D cameraOrigin = Vector3D(x_real, y_real, z_real);
//     cout << "Creating filename" << endl;
//     fileName = "Output/RTX_Test/frame" + to_string(frame) + ".ppm";
//     // Write the PPM header
//     cout << "ofstream" << endl;
//     ofstream ppmFile(fileName);
//     ppmFile << "P3\n";  // PPM file format (plain text)
//     ppmFile << CanvasWidth << " " << CanvasHeight
//             << "\n";     // Image dimensions: 3 pixels wide, 2 pixels high
//     ppmFile << "255\n";  // Maximum color value (8-bit)

//     cout << "Making Scene" << endl;
//     Scene scene =
//         makeScene(circle[frame % 360], circle[((int)frame + 120) % 360],
//                   circle[((int)frame + 240) % 360], frame);
//     cout << "Scene made" << endl;
//     render(scene, cameraOrigin);
//     cout << "Scene Rendered" << endl;

//     // This nested for loop maps the map2D values to the ppm file.
//     for (int x = 0; x < CanvasWidth; x++) {
//       for (int y = 0; y < CanvasHeight; y++) {
//         ppmFile << map2D[y][x];
//       }
//       ppmFile << "\n";
//     }

//     progress = int((frame / final_frame) * 100);
//     if (progress != prev) {
//       cout << "Loading... " << progress << "% done. Rendering frame " <<
//       frame
//            << " of " << int(final_frame) << endl;
//       prev = progress;
//     }
//   }

//   cout << "DONE!" << endl;
//   return 0;
// }