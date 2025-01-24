#pragma once
#include <vector>
#include "Primitive.h"
#include "Light.h"
using namespace std;

class Scene {
    public:
        // Attributes
        vector<Primitive> objects;
        vector<Light> lights;

        // Constructor (initializes the attribute)
        Scene(vector<Primitive> objects, vector<Light> lights);

        // Setters
        void setLights(vector<Light> lights);

        // Getters
        vector<Primitive> getObjects();

        vector<Light> getLights();
};

