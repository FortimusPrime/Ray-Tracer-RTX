#include "Scene.h"
Scene::Scene(vector<Primitive> objects, vector<Light> lights, Vector3D BACKGROUND_COLOR) {
  this->objects = objects;
  this->lights = lights;
  this->BACKGROUND_COLOR = BACKGROUND_COLOR;
}

// Setters
void Scene::setLights(vector<Light> lights) { this->lights = lights; }

// Getters
vector<Primitive> Scene::getObjects() { return this->objects; }

vector<Light> Scene::getLights() { return this->lights; }
