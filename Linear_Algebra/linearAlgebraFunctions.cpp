#include "linearAlgebraFunctions.h"

Vector3D getCrossProduct(Vector3D a, Vector3D b){
    double cx = a.getY() * b.getZ() - a.getZ() * b.getY();
    double cy = a.getZ() * b.getX() - a.getX() * b.getZ();
    double cz = a.getX() * b.getY() - a.getY() * b.getX();
    return Vector3D(cx, cy, cz);
}

double generateRandomNumber(double min, double max){
    // Set up random number generator
    random_device rd; // Seed
    mt19937 gen(rd()); // Mersenne Twister engine for generating random numbers
    uniform_int_distribution<> distrib(min, max); // Uniform distribution within [min, max]

    // Generate a random number within the range [min, max]
    double random_number = distrib(gen);
    return random_number;
}

Vector3D ColorMax(Vector3D color){
    array<double, 3> colorArray = {color.getX(), color.getY(), color.getZ()};
    for (int i = 0; i < 3; i++){
        if (colorArray[i] > 255){
            colorArray[i] = 255;
        }
        else if (colorArray[i] < 0){
            colorArray[i] = 0;
        }
    }
    Vector3D newColor = Vector3D(colorArray[0], colorArray[1], colorArray[2]);
    return newColor;
}

array<Vector3D, 360> circleCoordinates(){
    array<Vector3D, 360> list;
    double x;
    double y;
    int angle;
    double rads;
    for (angle = 0; angle <= 360; angle++){
        rads = angle*(3.14/180);
        x = std::cos(rads);
        y = std::sin(rads);
        list[angle] = Vector3D(x*2, y*2, 8);
    }
    return list;
}

double degreesToRadians(double deg){
    return deg * 3.14/180;
}

Matrix3D getRotationMatrix(double angleA, double angleB, double angleR){
    double angleAlpha = degreesToRadians(angleA);
    double angleBeta = degreesToRadians(angleB);
    double anglePhi = degreesToRadians(angleR);
    Vector3D vect1 = Vector3D(
        cos(angleBeta) * cos(anglePhi), 
        cos(angleBeta) * sin(anglePhi), 
        sin(angleBeta) * -1);
    Vector3D vect2 = Vector3D(
        sin(angleAlpha) * sin(angleBeta)*cos(anglePhi) - cos(angleAlpha) * sin(anglePhi), 
        sin(angleAlpha) * sin(angleBeta) * sin(anglePhi) + cos(angleAlpha) * cos(anglePhi), 
        sin(angleAlpha) * cos(angleBeta));
    Vector3D vect3 = Vector3D(
        cos(angleAlpha) * sin(angleBeta) * cos(anglePhi) + sin(angleAlpha) * sin(anglePhi), 
        cos(angleAlpha) * sin(angleBeta) * sin(anglePhi) - sin(angleAlpha) * cos(anglePhi), 
        cos(angleAlpha) * cos(angleBeta));
    Matrix3D rotationMatrix = Matrix3D(vect1, vect2, vect3);
    return rotationMatrix;
}