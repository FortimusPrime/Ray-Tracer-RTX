#include "Camera.h"

// Constructor (initializes the attribute)

Camera::Camera(double distanceViewportCamera, Vector3D cameraOrigin, int viewportWidth, int viewportHeight, int canvasWidth, int canvasHeight) {
  this->distanceViewportCamera = distanceViewportCamera;
  this->cameraOrigin = cameraOrigin;
  this->viewportWidth = viewportWidth;
  this->viewportHeight = viewportHeight;
  this->canvasWidth = canvasWidth;
  this->canvasHeight = canvasHeight;
}

// Getters

double Camera::getDistanceViewportCamera() { return this->distanceViewportCamera; };
Vector3D Camera::getCameraOrigin() { return this->cameraOrigin; }
int Camera::getViewportWidth() { return this->viewportWidth; }
int Camera::getViewportHeight() { return this->viewportHeight; }
int Camera::getCanvasWidth() { return this->canvasWidth; }
int Camera::getCanvasHeight() { return this->canvasHeight; }
