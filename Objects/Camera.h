#ifndef CAMERA_H
#define CAMERA_H

#include "../Linear_Algebra/Vector3D.h"
using namespace std;

/**
 * @class Camera
 * @brief Represents a virtual camera in a 3D scene.
 */
class Camera {
 public:
  /**
   * @brief Default constructor.
   */
  Camera();

  /**
   * @brief Construct a new Camera object
   *
   * @param distanceViewportCamera Distance from the viewport to the camera.
   * @param cameraOrigin Position of the camera in 3D space.
   * @param viewportWidth Width of the viewport.
   * @param viewportHeight Height of the viewport.
   * @param canvasWidth Width of the canvas.
   * @param canvasHeight Height of the canvas.
   */
  Camera(double distanceViewportCamera, Vector3D cameraOrigin, int viewportWidth, int viewportHeight, int canvasWidth, int canvasHeight);

  /**
   * @brief Gets the distance from the viewport to the camera.
   * @return Distance from the viewport to the camera.
   */
  double getDistanceViewportCamera();

  /**
   * @brief Gets the camera's origin position.
   *
   * @return Camera origin as a Vector3D.
   */
  Vector3D getCameraOrigin();

  /**
   * @brief Gets the viewport width.
   *
   * @return Viewport width.
   */
  int getViewportWidth();

  /**
   * @brief Gets the viewport height.
   *
   * @return Viewport height.
   */
  int getViewportHeight();

  /**
   * @brief Gets the canvas width.
   *
   * @return Canvas width.
   */
  int getCanvasWidth();

  /**
   * @brief Gets the canvas height.
   *
   * @return Canvas height.
   */
  int getCanvasHeight();

  // Attributes
  double distanceViewportCamera;
  Vector3D cameraOrigin;
  int viewportWidth;
  int viewportHeight;
  int canvasWidth;
  int canvasHeight;
};

#endif  // CAMERA_H