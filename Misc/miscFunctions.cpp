#include "miscFunctions.h"

const Vector3D ColorPalette::red = Vector3D(255, 0, 0);
const Vector3D ColorPalette::blue = Vector3D(0, 0, 255);
const Vector3D ColorPalette::green = Vector3D(0, 255, 0);
const Vector3D ColorPalette::yellow = Vector3D(255, 255, 0);
const Vector3D ColorPalette::cyan = Vector3D(0, 255, 255);
const Vector3D ColorPalette::magenta = Vector3D(255, 0, 255);
const Vector3D ColorPalette::orange = Vector3D(255, 165, 0);
const Vector3D ColorPalette::purple = Vector3D(128, 0, 128);
const Vector3D ColorPalette::pink = Vector3D(255, 192, 203);
const Vector3D ColorPalette::brown = Vector3D(165, 42, 42);
const Vector3D ColorPalette::gray = Vector3D(128, 128, 128);
const Vector3D ColorPalette::white = Vector3D(255, 255, 255);

/**
 * @brief Gets the current machine time.
 *
 * @return timespec the time of the machine.
 */
timespec getTime() {
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  return current_time;
}

/**
 * @brief Calculates the elapsed time starting from start_time.
 *
 * @param start_time The time from which to calculate the time elapsed. Must be timespec.
 * @return double The time elapsed.
 */
double calculateElapsedTime(timespec start_time) {
  struct timespec end_time;
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double elapsed = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
  return elapsed;
}

/**
 * @brief prints the Map2D values to the ppm file passed.
 *
 * @param CanvasWidth Variable for the width to map correctly.
 * @param CanvasHeight Variable for the height to map correctly.
 * @param ppmFile PPM file to print to.
 * @param map2D Grid containing values to map to.
 */
void map2DtoFile(int CanvasWidth, int CanvasHeight, ofstream& ppmFile, vector<vector<string>>& map2D) {
  for (int x = 0; x < CanvasWidth; x++) {
    for (int y = 0; y < CanvasHeight; y++) {
      ppmFile << map2D[y][x];
    }
    ppmFile << "\n";
  }
}

/**
 * @brief Creates a Scene object with the coordinates received for each floating primitive.
 *
 * @param coords1 Coordinates of first primitive. (Sphere)
 * @param coords2 Coordinates of second primitive (Cube)
 * @param coords3 Coordinates of third primitive (Tetrahedron)
 * @param BACKGROUND_COLOR Color for the background.
 * @param angleInput The angle for the spin on the circle.
 * @return Scene a Scene object to render with the current parameters.
 */
Scene makeScene(Vector3D coords1, Vector3D coords2, Vector3D coords3, Vector3D BACKGROUND_COLOR, double angleInput) {
  // Create Objects
  Primitive ground_sphere = Primitive(Vector3D(0, -5050, 100), 5000, ColorPalette::green, 0, 0.0);
  Primitive sphere = Primitive(coords1, 1, ColorPalette::blue, 500, 0.3);

  array<Primitive, 4> tetra = buildTetrahedron2(Vector3D(255, 255, 0), coords3, 1, 25, 0.0, angleInput);  // Tip

  vector<Primitive> objects;
  objects.push_back(ground_sphere);
  objects.push_back(sphere);

  for (int i = 0; i <= 3; i++) {
    objects.push_back(tetra[i]);
  }

  array<Primitive, 12> cube = buildCube(coords2, 0.8, ColorPalette::red, angleInput);
  for (int i = 0; i < 12; i++) {
    objects.push_back(cube[i]);
  }

  Light light1 = Light("ambient", 0.2, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
  Light light2 = Light("point", 0.6, Vector3D(2, 1, 0), Vector3D(0, 0, 0));
  Light light3 = Light("directional", 0.2, Vector3D(0, 0, 0), Vector3D(1, 4, 4));
  Light light4 = Light("point", 0.6, Vector3D(2, 1, 0), Vector3D(0, 0, 0));
  Light light5 = Light("point", 0.2, Vector3D(-2, 1, 0), Vector3D(0, 0, 0));

  vector<Light> lights;
  lights.push_back(light1);
  lights.push_back(light2);
  lights.push_back(light3);
  lights.push_back(light4);
  lights.push_back(light5);

  Scene scene = Scene(objects, lights, BACKGROUND_COLOR);
  return scene;
}