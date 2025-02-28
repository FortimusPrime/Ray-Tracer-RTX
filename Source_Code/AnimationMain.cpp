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
#include "../Misc/miscFunctions.h"
#include "../Objects/Primitive.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"
#include "../Ray-Tracing/RayTracingFunctions.h"

using namespace std;

int main() {
  timespec start_time = getTime();  // To profile time.
  Config config;
  // Viewport Dims
  config.ViewportWidth = 1;
  config.ViewportHeight = 1;

  // Canvas Dims
  config.CanvasWidth = 100;
  config.CanvasHeight = 100;

  config.distance_viewport_camera = 1;

  Vector3D BACKGROUND_COLOR = Vector3D(0, 255, 255);  // Cyan
  double x_real = 0.0, y_real = 0.0, z_real = 1.0;    // Coordinates for camera. Initialized to 0.0 and 1.0 as the center.
  Vector3D cameraOrigin;
  string fileName;
  array<Vector3D, 360> circleCoords = circleCoordinates();  // Calculate the circle coordinates for spinning primitives. 0, 1, 8 is the center of the circle

  int prev = -1;                 // For later down below.
  int progress = 0;              // Current progress in frames.
  double final_frame = 360 * 2;  // Final frame for the render.

  double result = 0;
  for (int frame = (360 * 2) - 1; frame < final_frame; frame++) {  // Loop to make frames. Each loop renders a new frame.
    result = 0.25 * (360.0 / (0.5 * (frame + 1)));                 // Calculate the depth of the camera using the frame value for the tracking animation
    if (frame < 360 || result > 0.7) {                             // Clamping to stop camera from movement after a certain point.
      z_real = result;
    }
    // cameraOrigin = Vector3D(x_real, y_real, z_real); // Commented for single frame to stay in center.

    fileName = "../Output/RTX_Test/framenew" + to_string(frame) + ".ppm";
    ofstream ppmFile(fileName);
    ppmFile << "P3\n" << config.CanvasWidth << " " << config.CanvasHeight << "\n" << "255\n";  // Write the PPM header: P3 -> PPM file format (plain text) | CanvasWidth, CanvasHeight -> Image dimensions | 255 -> Maximum color value (8-bit)

    Scene scene = makeScene(circleCoords[frame % 360], circleCoords[(frame + 120) % 360], circleCoords[(frame + 240) % 360], BACKGROUND_COLOR, frame);
    vector<vector<string>> map2D = render(scene, cameraOrigin, config);    // Since render will be parallel, it will be stored on a 2D vector to later map to file.
    map2DtoFile(config.CanvasWidth, config.CanvasHeight, ppmFile, map2D);  // Mapping Map2D results to ppm file.

    // Calculate animation progress.
    progress = int((frame / final_frame) * 100);
    if (progress != prev) {
      cout << "Loading... " << progress << " done. Rendering frame " << frame << " of " << int(final_frame) << endl;
      prev = progress;
    }
  }
  double elapsed = calculateElapsedTime(start_time);  // Calculate time elapsed.
  printf("DONE! Execution time: %f seconds\n", elapsed);
  return 0;
}