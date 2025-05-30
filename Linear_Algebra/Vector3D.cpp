#include "Vector3D.h"
// Constructor
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Overloads
Vector3D Vector3D::operator+(const Vector3D& other) const { return Vector3D(x + other.x, y + other.y, z + other.z); }

Vector3D Vector3D::operator-(const Vector3D& other) const { return Vector3D(x - other.x, y - other.y, z - other.z); }

Vector3D Vector3D::operator*(double scalar) const { return Vector3D(x * scalar, y * scalar, z * scalar); }

Vector3D Vector3D::operator/(double scalar) const { return Vector3D(x / scalar, y / scalar, z / scalar); }

double Vector3D::operator*(const Vector3D& other) const { return x * other.x + y * other.y + z * other.z; }

bool Vector3D::operator==(const Vector3D& other) const { return x == other.x && y == other.y && z == other.z; }

// Magnitude of the vector
double Vector3D::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

// Normalize the vector
Vector3D Vector3D::normalize() const {
  double mag = magnitude();
  return Vector3D(x / mag, y / mag, z / mag);
}

// Getters
double Vector3D::getX() const { return this->x; }
double Vector3D::getY() const { return this->y; }
double Vector3D::getZ() const { return this->z; }

// Print the vector (for debugging)
void Vector3D::print() const { std::cout << "(" << x << ", " << y << ", " << z << ")\n"; }