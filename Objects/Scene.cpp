#include "Scene.h"
    Scene::Scene(vector<Primitive> objects, vector<Light> lights){
        this->objects = objects;
        this->lights = lights;
    }

    // Setters
    void Scene::setLights(vector<Light> lights){
        this->lights = lights;
    }

    // Getters
    vector<Primitive> Scene::getObjects(){
        return this->objects;
    }

    vector<Light> Scene::getLights(){
        return this->lights;
    }
