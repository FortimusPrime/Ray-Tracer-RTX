#include "derivedObjects.h"
array<Primitive, 4> buildTetrahedron(Vector3D color, Vector3D pointA, Vector3D pointB, Vector3D pointC, Vector3D pointD, int specular, double reflective){

    Primitive t1 = Primitive(Vector3D(255, 0, 0), pointA, pointB, pointC, specular, reflective);
    Primitive t2 = Primitive(Vector3D(0, 255, 0), pointA, pointC, pointD, specular, reflective);
    Primitive t3 = Primitive(Vector3D(0, 0, 255), pointA, pointD, pointB, specular, reflective);
    Primitive t4 = Primitive(Vector3D(255, 255, 0), pointB, pointC, pointD, specular, reflective);

    array<Primitive, 4> triangles = {t1, t2, t3, t4};
    return triangles;
}
 

array<Primitive, 4> buildTetrahedron2(Vector3D color, Vector3D center, double width, int specular, double reflective, double angleInput){
    Matrix3D rotationMatrix = getRotationMatrix(angleInput*1, angleInput*2, angleInput*3);

    Vector3D pointA = (rotationMatrix * (Vector3D(center.getX(), center.getY(), center.getZ()-width) - center)) + center; // Tip
    Vector3D pointB = (rotationMatrix * (Vector3D(center.getX(), center.getY()+width, center.getZ()+width) - center)) + center;
    Vector3D pointC = (rotationMatrix * (Vector3D(center.getX()-width, center.getY()-width, center.getZ()+width) - center)) + center;
    Vector3D pointD = (rotationMatrix * (Vector3D(center.getX()+width, center.getY()-width, center.getZ()+width) - center)) + center;

    Primitive t1 = Primitive(Vector3D(255, 0, 0), pointA, pointB, pointC, specular, reflective);
    Primitive t2 = Primitive(Vector3D(255, 255, 0), pointA, pointC, pointD, specular, reflective);
    Primitive t3 = Primitive(Vector3D(0, 0, 255), pointA, pointD, pointB, specular, reflective);
    Primitive t4 = Primitive(Vector3D(255, 192, 203), pointB, pointC, pointD, specular, reflective);

    array<Primitive, 4> triangles = {t1, t2, t3, t4};
    return triangles;
}


array<Primitive, 12> buildCube(Vector3D center, double width, Vector3D color, double angleInput){

    Matrix3D rotationMatrix = getRotationMatrix(angleInput*-1, angleInput*-2, angleInput * -1.5);

    int specular = 25; 
    double reflective = 0;

    // Top Plane Coordinates
    Vector3D topCornerLR = (rotationMatrix * (Vector3D(center.getX()-width, center.getY()+width, center.getZ()-width) - center)) + center; // Top Left Rear Corner
    Vector3D topCornerRR = (rotationMatrix * (Vector3D(center.getX()+width, center.getY()+width, center.getZ()-width) - center)) + center; // Top Right Rear Corner
    Vector3D topCornerRF = (rotationMatrix * (Vector3D(center.getX()+width, center.getY()+width, center.getZ()+width) - center)) + center; // Top Right Front Corner
    Vector3D topCornerLF = (rotationMatrix * (Vector3D(center.getX()-width, center.getY()+width, center.getZ()+width) - center)) + center; // Top Left Front Corner

    // Lower Plane Coordinates
    Vector3D bottomCornerLR = (rotationMatrix * (Vector3D(center.getX()-width, center.getY()-width, center.getZ()-width) - center)) + center; // Bottom Left Rear Corner
    Vector3D bottomCornerRR = (rotationMatrix * (Vector3D(center.getX()+width, center.getY()-width, center.getZ()-width) - center)) + center; // Bottom Right Rear Corner
    Vector3D bottomCornerRF = (rotationMatrix * (Vector3D(center.getX()+width, center.getY()-width, center.getZ()+width) - center)) + center; // Bottom Right Front Corner
    Vector3D bottomCornerLF = (rotationMatrix * (Vector3D(center.getX()-width, center.getY()-width, center.getZ()+width) - center)) + center; // Bottom Left Front Corner

    // Top Triangles
    Primitive t1 = Primitive(color, topCornerLR, topCornerRR, topCornerLF, specular, reflective);
    Primitive t2 = Primitive(color, topCornerRR, topCornerLF, topCornerRF, specular, reflective);

    // Bottom Triangles
    Primitive t3 = Primitive(color, bottomCornerLR, bottomCornerRR, bottomCornerLF, specular, reflective);
    Primitive t4 = Primitive(color, bottomCornerRR, bottomCornerLF, bottomCornerRF, specular, reflective);

    // Front Triangles
    Primitive t5 = Primitive(color, topCornerLF, bottomCornerLF, bottomCornerRF, specular, reflective);
    Primitive t6 = Primitive(color, topCornerRF, topCornerLF, bottomCornerRF, specular, reflective);

    // Rear Triangles
    Primitive t7 = Primitive(color, bottomCornerLR, bottomCornerRR, topCornerRR, specular, reflective);
    Primitive t8 = Primitive(color, bottomCornerLR, topCornerLR, topCornerRR, specular, reflective);

    // Left Triangles
    Primitive t9 = Primitive(color, topCornerLF, bottomCornerLF, bottomCornerLR, specular, reflective);
    Primitive t10 = Primitive(color, bottomCornerLR, topCornerLR, topCornerLF, specular, reflective);

    // Right Triangles
    Primitive t11 = Primitive(color, topCornerRF, bottomCornerRF, bottomCornerRR, specular, reflective);
    Primitive t12 = Primitive(color, bottomCornerRR, topCornerRR, topCornerRF, specular, reflective);

    array<Primitive, 12> triangles = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
    return triangles;
}
