#include "Light.h"

    // Constructor (initializes the attribute)
    Light::Light(string type, double intensity, Vector3D position, Vector3D direction) {
        this->type = type;
        this->intensity = intensity;
        this->position = position;
        this->direction = direction;
    }

    // Getters
    string Light::getType(){
        return this->type;
    }

    double Light::getIntensity(){
        return this->intensity;
    }

    // Getters
    Vector3D Light::getPosition(){
        return this->position;
    }

    // Getters
    Vector3D Light::getDirection(){
        return this->direction;
    }
