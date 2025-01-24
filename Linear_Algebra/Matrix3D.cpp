#include "Matrix3D.h"
    // Constructor
    Matrix3D::Matrix3D(Vector3D colX, Vector3D colY, Vector3D colZ) : colX(colX), colY(colY), colZ(colZ) {}

    Vector3D Matrix3D::operator * (Vector3D vector) const {
        double vectX = (this->getX0() * vector.getX()) + (this->getY0() * vector.getY()) + (this->getZ0() * vector.getZ());
        double vectY = (this->getX1() * vector.getX()) + (this->getY1() * vector.getY()) + (this->getZ1() * vector.getZ());
        double vectZ = (this->getX2() * vector.getX()) + (this->getY2() * vector.getY()) + (this->getZ2() * vector.getZ());
        return Vector3D(vectX, vectY, vectZ);
    }

    // Getters
    // Rows
    Vector3D Matrix3D::getRow0() const {
        return Vector3D(this->colX.getX(), this->colX.getY(), this->colX.getZ());
    }
    Vector3D Matrix3D::getRow1() const {
        return Vector3D(this->colY.getX(), this->colY.getY(), this->colY.getZ());
    }
    Vector3D Matrix3D::getRow2() const {
        return Vector3D(this->colZ.getX(), this->colZ.getY(), this->colZ.getZ());
    }

    // Columns
    Vector3D Matrix3D::getCol0() const {
        return this-> colX;
    }
    Vector3D Matrix3D::getCol1() const {
        return this-> colY;
        
    }
    Vector3D Matrix3D::getCol2() const {
        return this-> colY;
    }


    // First Column : X
    double Matrix3D::getX0() const{
        return this-> colX.getX();
    }

    double Matrix3D::getX1() const{
        return this-> colX.getY();
    }

    double Matrix3D::getX2() const{
        return this-> colX.getZ();
    }

    // Second Column : Y
    double Matrix3D::getY0() const{
        return this-> colY.getX();
    }

    double Matrix3D::getY1() const{
        return this-> colY.getY();
    }

    double Matrix3D::getY2() const{
        return this-> colY.getZ();
    }

    // Third col : Z
    double Matrix3D::getZ0() const{
        return this-> colZ.getX();
    }

    double Matrix3D::getZ1() const{
        return this-> colZ.getY();
    }

    double Matrix3D::getZ2() const{
        return this-> colZ.getZ();
    }


    // Print the vector (for debugging)
    void Matrix3D::print() const {
        std::cout << "[" << Matrix3D::getX0() << ", " << Matrix3D::getY0() << ", " << Matrix3D::getZ0() << "]\n"
                  << "[" << Matrix3D::getX1() << ", " << Matrix3D::getY1() << ", " << Matrix3D::getZ1() << "]\n"
                  << "[" << Matrix3D::getX2() << ", " << Matrix3D::getY2() << ", " << Matrix3D::getZ2() << "]\n";
    }