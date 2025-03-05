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
#include "../Objects/Camera.h"
#include "../Objects/Primitive.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"
#include "../Ray-Tracing/RayTracingFunctions.h"

using namespace std;

int main() {
  timespec startTime = getTime();  // To profile time.
  Camera camera = Camera(1, Vector3D(0, 0, 1), 1, 1, 800, 800);
  Vector3D BACKGROUND_COLOR = Vector3D(0, 255, 255);  // Cyan
  double x_real = 0.0, y_real = 0.0, z_real = 1.0;    // Coordinates for camera. Initialized to 0.0 and 1.0 as the center.
  string fileName;
  array<Vector3D, 360> circleCoords = circleCoordinates();  // Calculate the circle coordinates for spinning primitives. 0, 1, 8 is the center of the circle

  int prev = -1;                // For later down below.
  int progress = 0;             // Current progress in frames.
  double finalFrame = 360 * 2;  // Final frame for the render.

  double result = 0;
  for (int frame = (360 * 2) - 1; frame < finalFrame; frame++) {  // Loop to make frames. Each loop renders a new frame.
    result = 0.25 * (360.0 / (0.5 * (frame + 1)));                // Calculate the depth of the camera using the frame value for the tracking animation
    if (frame < 360 || result > 0.7) {                            // Clamping to stop camera from movement after a certain point.
      z_real = result;
    }

    fileName = "../Output/RTX_Test/framenew" + to_string(frame) + ".ppm";
    ofstream ppmFile(fileName);
    ppmFile << "P3\n" << camera.getCanvasWidth() << " " << camera.getCanvasHeight() << "\n" << "255\n";  // Write the PPM header: P3 -> PPM file format (plain text) | CanvasWidth, CanvasHeight -> Image dimensions | 255 -> Maximum color value (8-bit)

    Scene scene = makeScene(circleCoords[frame % 360], circleCoords[(frame + 120) % 360], circleCoords[(frame + 240) % 360], BACKGROUND_COLOR, frame);
    vector<vector<string>> map2D = render(scene, camera);                            // Since render will be parallel, it will be stored on a 2D vector to later map to file.
    map2DtoFile(camera.getCanvasWidth(), camera.getCanvasHeight(), ppmFile, map2D);  // Mapping Map2D results to ppm file.

    // Calculate animation progress.
    progress = int((frame / finalFrame) * 100);
    if (progress != prev) {
      cout << "Loading... " << progress << " done. Rendering frame " << frame << " of " << int(finalFrame) << endl;
      prev = progress;
    }
  }
  double elapsed = calculateElapsedTime(startTime);  // Calculate time elapsed.
  printf("DONE! Execution time: %f seconds\n", elapsed);
  return 0;
}