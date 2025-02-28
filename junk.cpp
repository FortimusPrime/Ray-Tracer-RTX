// int mainAUX() {
//   double x_real = 0.0;
//   double y_real = 0.0;
//   double z_real = 0;

//   string fileName;
//   int count = 0;
//   array<Vector3D, 360> circle = circleCoordinates();

//   int prev = -1;
//   int progress = 0;
//   double final_frame = 360 * 2;
//   // double final_frame = 1;

//   double result = 0;
//   for (int frame = 360; frame < final_frame; frame++) {
//     // Calculate the depth of the camera for the tracking animation
//     result = 0.25 * (360.0 / (0.5 * (frame + 1)));

//     if (frame < 360 || result > 0.7) {
//       z_real = result;
//     }

//     cout << "Camera " << z_real << endl;
//     Vector3D cameraOrigin = Vector3D(x_real, y_real, z_real);
//     cout << "Creating filename" << endl;
//     fileName = "Output/RTX_Test/frame" + to_string(frame) + ".ppm";
//     // Write the PPM header
//     cout << "ofstream" << endl;
//     ofstream ppmFile(fileName);
//     ppmFile << "P3\n";  // PPM file format (plain text)
//     ppmFile << CanvasWidth << " " << CanvasHeight
//             << "\n";     // Image dimensions: 3 pixels wide, 2 pixels high
//     ppmFile << "255\n";  // Maximum color value (8-bit)

//     cout << "Making Scene" << endl;
//     Scene scene =
//         makeScene(circle[frame % 360], circle[((int)frame + 120) % 360],
//                   circle[((int)frame + 240) % 360], frame);
//     cout << "Scene made" << endl;
//     render(scene, cameraOrigin);
//     cout << "Scene Rendered" << endl;

//     // This nested for loop maps the map2D values to the ppm file.
//     for (int x = 0; x < CanvasWidth; x++) {
//       for (int y = 0; y < CanvasHeight; y++) {
//         ppmFile << map2D[y][x];
//       }
//       ppmFile << "\n";
//     }

//     progress = int((frame / final_frame) * 100);
//     if (progress != prev) {
//       cout << "Loading... " << progress << "% done. Rendering frame " <<
//       frame
//            << " of " << int(final_frame) << endl;
//       prev = progress;
//     }
//   }

//   cout << "DONE!" << endl;
//   return 0;
// }