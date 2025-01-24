// To Run: clang++ -Xpreprocessor -fopenmp -lomp -I/opt/homebrew/Cellar/libomp/19.1.3/include -L/opt/homebrew/Cellar/libomp/19.1.3/lib simple_parallel.cpp -o parallel_example && ./parallel_example
//  clang++ -Xpreprocessor -fopenmp -lomp -I/opt/homebrew/Cellar/libomp/19.1.3/include -L/opt/homebrew/Cellar/libomp/19.1.3/lib simple_parallel.cpp -o parallel_example && ./parallel_example
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <memory>
#include <random>
#include "../Linear_Algebra/linearAlgebraFunctions.h"
#include "../Objects/Primitive.h"
#include "../Linear_Algebra/Vector3D.h"
#include "../Objects/Scene.h"
#include "../Objects/derivedObjects.h"
#include "../Ray-Tracing/RayTracingFunctions.h"
using namespace std;

// Global Vars
int distance_viewport_camera = 1; 
int inf = 2147483647; 
int recursion_depth = 5; 

// Viewport Dims
int ViewportWidth = 1; 
int ViewportHeight = 1; 

// Canvas Dims
int CanvasWidth = 800; 
int CanvasHeight = 800;

// These are the canvas coordinates in which the parallel processing will be mapping the color vectors to. Adjust width accordingly. 
array<array<string, 800>, 800> map2D;
string colorToMap;

Vector3D red = Vector3D(255, 0, 0);
Vector3D blue = Vector3D(0, 0, 255);
Vector3D green = Vector3D(0, 255, 0);
Vector3D yellow = Vector3D(255, 255, 0);
Vector3D cyan = Vector3D(0, 255, 255);
Vector3D magenta = Vector3D(255, 0, 255);
Vector3D orange = Vector3D(255, 165, 0);
Vector3D purple = Vector3D(128, 0, 128);
Vector3D pink = Vector3D(255, 192, 203);
Vector3D brown = Vector3D(165, 42, 42);
Vector3D gray = Vector3D(128, 128, 128);
Vector3D white = Vector3D(255, 255, 255);

Vector3D BACKGROUND_COLOR = cyan;

Scene makeScene(){
     // Create Objects
    Primitive triangle = Primitive(pink, Vector3D(0, -1, 3), Vector3D(2, 0, 4), Vector3D(-2, 0, 4), 1000, 0.0);
    Primitive triangle2 = Primitive(Vector3D(128, 0, 128), Vector3D(0, 0, 2), Vector3D(1, 2, 2), Vector3D(-1, 2, 2), 1000, 0.0);

    Primitive sphere1 = Primitive(Vector3D(0, -5001, 0), 5000, green, 0, 0.0);
    Primitive sphere2 = Primitive(Vector3D(2, 0, 8), 1, blue, 500, 0.3);
    Primitive sphere3 = Primitive(Vector3D(-2, 0, 8), 1, orange, 10, 0.4);
    Primitive sphere4 = Primitive(Vector3D(0, -1, 7), 1, red, 500, 0.2);
    Primitive sphere5 = Primitive(Vector3D(1, -1, 8), 0.5, white, 500, 0.2);
    // Primitive sphere6 = Primitive(Vector3D(1, -1, 8), 0.5, white, 500, 0.2);
    

    Primitive coordSphere = Primitive(Vector3D(20, 30, 100), 10, yellow, 1000, 0);

    array<Primitive, 4> tetra = buildTetrahedron(Vector3D(255, 255, 0),
    Vector3D(0, 0, 2), // Tip: X, Z, Y
    Vector3D(0.5, 0.5, 4), // Side Right
    Vector3D(0.5, -0.5, 4), 
    Vector3D(-0.5, 0, 4), 1000, 0.0); // Tip

    vector<Primitive> objects; 
    objects.push_back(sphere1);
    objects.push_back(sphere2); 
    objects.push_back(sphere3); 
    objects.push_back(sphere4);
    objects.push_back(sphere5);
    // objects.push_back(triangle);
    // objects.push_back(triangle2);

    for (int i = 0; i <= 3; i++){
        objects.push_back(tetra[i]);
    }

    objects.push_back(coordSphere); 

    array<Primitive, 12> cube = buildCube(Vector3D(-2, 3, 10), 1, magenta);
    for (int i = 0; i < 12; i++){
        objects.push_back(cube[i]);
    }

    int xDistance;
    int yDistance;
    int zDistance;
    int R;
    int G;
    int B;
    double sphereRadius;
    Primitive newSphere;
    for (int i = 0; i < 0; i++){
        xDistance = generateRandomNumber(-5, 5);
        yDistance = generateRandomNumber(0, 10);
        zDistance = generateRandomNumber(10, 15);
        sphereRadius = generateRandomNumber(0.5, 1);
        R = generateRandomNumber(0, 255);
        G = generateRandomNumber(0, 255);
        B = generateRandomNumber(0, 255);
        
        newSphere = Primitive(Vector3D(xDistance, yDistance, zDistance), sphereRadius, Vector3D(R, G, B), 1000, 0.1);
        objects.push_back(newSphere);
    }


    Light light1 = Light("ambient", 0.2, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    Light light2 = Light("point", 0.6, Vector3D(2, 1, 0), Vector3D(0, 0, 0));
    Light light3 = Light("directional", 0.2, Vector3D(0, 0, 0), Vector3D(1, 4, 4));
    Light light4 = Light("point", 0.6, Vector3D(3, 2, 7), Vector3D(0, 0, 0));
    Light light5 = Light("point", 0.2, Vector3D(-2, 1, 0), Vector3D(0, 0, 0));

    vector<Light> lights;
    lights.push_back(light1);
    lights.push_back(light2);
    lights.push_back(light3);
    lights.push_back(light4);
    lights.push_back(light5);
    
    Scene scene = Scene(objects, lights);
    return scene;
}

void render(Scene scene, Vector3D cameraOrigin){
// Render scene and update on progress. 
    int whole = CanvasWidth * CanvasHeight; 
    double current = 0;
    int prev = -1;
    int progress = 0;

    // My idea:
        // We could have a tensor, that is a 2D matrix which would represent each point in the canvas, and it would be assigned it's index. 
        // That way, after the parallel operation, we could "paint" on the canvas 

    #pragma omp parallel for
    for (int x = -CanvasWidth/2; x < CanvasWidth/2; x++){
        for (int y = -CanvasHeight/2; y < CanvasHeight/2; y++){
            Vector3D D = CanvasToViewport(y, -x, ViewportWidth, ViewportHeight, CanvasWidth, CanvasHeight, distance_viewport_camera); // NOTE, the second value is 0, when in Python it's 0.5 
            D = D/D.magnitude();
            Vector3D color = TraceRay(cameraOrigin, D, double(distance_viewport_camera), inf, recursion_depth, scene, BACKGROUND_COLOR);
            color = ColorMax(color);
            // colorToMap is the temporary which will take the color and map it to the map2D
            colorToMap = to_string(int(color.getX())) + " " + to_string(int(color.getY())) + " " + to_string(int(color.getZ())) + "   "; 
            // Since values tend to go to the negatives, we add the offset to map correctly to the map2D 
            map2D[y + CanvasHeight/2][x + CanvasWidth/2] = colorToMap;
            
            #pragma omp atomic
            // Increase the progress
            current ++;
            progress = int((current/whole)*100);

        }
        
        #pragma omp critical
        // Cout the progress if there has been a change in percentage. 
        if (progress != prev){
            cout << "Loading... " << progress << "% done." << endl;
            prev = progress;
        }
    }    
}

int main() {
    double x_real = 0.0f; 
    double y_real = 0.0f; 
    double z_real = 0.0f; 
    Vector3D cameraOrigin = Vector3D(x_real, y_real, z_real); 

    string fileName;
    fileName = "Output/render.ppm";
    // Write the PPM header
    ofstream ppmFile(fileName);
    ppmFile << "P3\n";         // PPM file format (plain text)
    ppmFile << CanvasWidth << " " << CanvasHeight << "\n";        // Image dimensions: 3 pixels wide, 2 pixels high
    ppmFile << "255\n";        // Maximum color value (8-bit)
 
    Scene scene = makeScene();
    render(scene, cameraOrigin);

    // This nested for loop maps the map2D values to the ppm file. 
    for (int x = 0; x < CanvasWidth; x++){
        for (int y = 0; y < CanvasHeight; y++){
            ppmFile << map2D[y][x];
        }
        ppmFile << "\n";
    }

    cout << "DONE!" << endl;
    return 0;
}