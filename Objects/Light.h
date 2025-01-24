#pragma once
#include <string>
#include "../Linear_Algebra/Vector3D.h"
using namespace std;

class Light {
    public:
        Light() : type("light") {}

        // Constructor (initializes the attribute)
        Light(string type, double intensity, Vector3D position, Vector3D direction);

        // Virtual destructor to make 'Light' polymorphic
        virtual ~Light() {}

        // Getters
        string getType();

        double getIntensity();

        // Getters
        Vector3D getPosition();

        // Getters
        Vector3D getDirection();

    protected:
        // Attributes
        string type;
        double intensity;
        Vector3D position;
        Vector3D direction;
};
