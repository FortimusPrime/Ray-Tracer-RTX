#ifndef SCENE_H
#define SCENE_H
#include <vector>

#include "Light.h"
#include "Primitive.h"
using namespace std;

class Scene {
 public:
  // Attributes
  vector<Primitive> objects;
  vector<Light> lights;
  Vector3D BACKGROUND_COLOR;

  // Constructor (initializes the attribute)
  Scene(vector<Primitive> objects, vector<Light> lights, Vector3D BACKGROUND_COLOR);

  // Setters
  void setLights(vector<Light> lights);

  // Getters
  vector<Primitive> getObjects();

  vector<Light> getLights();
};

#endif  // SCENE_H