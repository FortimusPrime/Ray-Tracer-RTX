#include "RayTracingFunctions.h"

Vector3D reflectRay(Vector3D R, Vector3D N){
    Vector3D result = (N * 2.0 * (N * R)) - R;
    return result;
}

// Alternative Function
// bool pointInTriangle(Vector3D P, Primitive triangle){
//     // We will use barycentric coordinates
//     Vector3D A = triangle.getPointA();
//     Vector3D B = triangle.getPointB();
//     Vector3D C = triangle.getPointC();

//     // Calculate vectors AB, BC, CA
//     Vector3D AB = B - A;
//     Vector3D BC = C - B;
//     Vector3D CA = A - C;

//     // Calculate vectors from A, B, C to P
//     Vector3D AP = P - A;
//     Vector3D BP = P - B;
//     Vector3D CP = P - C;

//     // Calculate cross products
//     Vector3D cross1 = getCrossProduct(AB, AP); // AB x AP
//     Vector3D cross2 = getCrossProduct(BC, BP); // BC x BP
//     Vector3D cross3 = getCrossProduct(CA, CP); // CA x CP

//     // Calculate reference cross products for each triangle edge with the remaining vertex
//     Vector3D refCross1 = getCrossProduct(AB, (C - A)); // AB x AC
//     Vector3D refCross2 = getCrossProduct(BC, (A - B)); // BC x BA
//     Vector3D refCross3 = getCrossProduct(CA, (B - C)); // CA x CB

//     // Check if dot products have the same sign for all edges
//     bool sameSide1 = cross1 * (refCross1) >= 0;
//     bool sameSide2 = cross2 * (refCross2) >= 0;
//     bool sameSide3 = cross3 * (refCross3) >= 0;

//     // If all cross products have the same sign, P is inside the triangle
//     return sameSide1 && sameSide2 && sameSide3;
//     return false;
// }


bool pointInTriangle(const Vector3D &P, Primitive triangle) {
    Vector3D A = triangle.getPointA();
    Vector3D B = triangle.getPointB();
    Vector3D C = triangle.getPointC();

    Vector3D v0 = C - A;
    Vector3D v1 = B - A;
    Vector3D v2 = P - A;

    double dot00 = v0 * v0;
    double dot01 = v0 * v1;
    double dot02 = v0 * v2;
    double dot11 = v1 * v1;
    double dot12 = v1 * v2;

    double invDenom = 1.0/(dot00*dot11-dot01*dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

array<double, 2> IntersectRayTriangle(Vector3D O, Vector3D D, Primitive triangle){

    Vector3D P0 = triangle.getPointA();
    Vector3D P1 = triangle.getPointB();
    Vector3D P2 = triangle.getPointC();

    double t1 = 0.0;
    double t2 = 0.0;
    double t = 0.0;

    Vector3D edge1 = P1 - P0;
    Vector3D edge2 = P2 - P0;
    Vector3D normal = getCrossProduct(edge1, edge2);

    double NdotD = normal * D;
    if (NdotD == 0) {
        t1 = 2147483647;
        t2 = 2147483647;
    }

    t = (normal * (P0 - O)) / NdotD;
    if (t < 0) {
        t1 = 2147483647;
        t2 = 2147483647;
    }

    Vector3D P = O + D * t;

    if (pointInTriangle(P, triangle)) {
        t1 = t;
        t2 = 2147483647;
    } else {
        t1 = 2147483647;
        t2 = 2147483647;
    }
    // // If the cross product of the normal of the plane and the ray are 0, they are parallel and will never intersect. 
    // // That is, if cross(D, TriangleNormal) == 0, we return the background color. 
    // double t1 = 0.0;
    // double t2 = 0.0;
    // double t = 0.0;

    // if (triangle.getNormal() * D == 0){
    //     t1 = inf;
    //     t2 = inf;
    // }
    // else{
    //     // Now, if the triangle normal and the ray are not parallel, with maths, we need to find the intersection point. That is, T. 

    //     double d = triangle.getNormal() * triangle.getPointA();
    //     double t = ((triangle.getNormal() * O) + d) / (triangle.getNormal() * D);

    //     Vector3D point = O + D*t;
    //     if (!pointInTriangle(point, triangle)){
    //         t = -1;
    //     }
    //     t1 = t;
    //     t2 = inf;
    // }
    array<double, 2> result = {t1, t2}; // For this case, to use the same functions for both triangles and spheres, we'll just place t in both spaces of the pair. 
    return result;
}

array<double, 2> IntersectRaySphere(Vector3D O, Vector3D D, Primitive sphere) {
    
    double r = sphere.getRadius();
    Vector3D CO = O - sphere.center;
    double a = D * D;
    double b = 2*(CO * D);
    double c = (CO * CO) - r*r;

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        array<double, 2> result = {2147483647, 2147483647};
        return result;
    }

    double t1 = (-b + sqrt(discriminant)) / (2*a);
    double t2 = (-b - sqrt(discriminant)) / (2*a);
    array<double, 2> result = {t1, t2};
    return result;
}

array<double, 2> ClosestIntersection(Vector3D cameraOrigin, Vector3D D, double t_min, double t_max, Scene scene) {
    double closest_t = 2147483647;
    int closest_object_index = -1;  // Use index instead of pointer
    for (int i = 0; i < int(scene.getObjects().size()); i++) {
        Primitive currentObject = scene.getObjects()[i];
        array<double, 2> ts = {0, 0};
        
        if (currentObject.getType() == "sphere"){
            ts = IntersectRaySphere(cameraOrigin, D, currentObject);
        }
        else {
            ts = IntersectRayTriangle(cameraOrigin, D, currentObject);
        }
        double t1 = ts[0];
        double t2 = ts[1];

        if (t_min < t1 && t1 < t_max && t1 < closest_t){
            closest_t = t1;
            closest_object_index = i;  // Store the index
        }

        if (t_min < t2 && t2 < t_max && t2 < closest_t) {
            closest_t = t2;
            closest_object_index = i;  // Store the index
        }
    }
    array<double, 2> result = {double(closest_object_index), closest_t};
    return result;
}

double ComputeLighting(Vector3D P, Vector3D N, Vector3D V, int s, Scene scene) {
    double intensity = 0.0;
    int t_max = 2147483647;
    Vector3D L = Vector3D(0, 0, 0);
    for (int index = 0; index < int(scene.getLights().size()); index++) {
        Light light = scene.getLights()[index];

        if (light.getType() == "ambient") {
            intensity = intensity + light.getIntensity();
        } else {
            if (light.getType() == "point") {
                L = light.getPosition() - P;
                t_max = 1;
            } else {
                L = light.getDirection();
                t_max = 2147483647;
            }
            // Shadow check
            array<double, 2> shadows = ClosestIntersection(P, L, 0.001, t_max, scene);
            double shadow_sphere_index = shadows[0];

            if (shadow_sphere_index != -1) {
                continue;
            }
             // Diffuse
            double n_dot_l = N * L;
            if (n_dot_l > 0) {
                intensity = intensity + ((light.getIntensity() * n_dot_l)/(N.magnitude() * L.magnitude()));
            }
            // Specular
            if (s != -1) {
                Vector3D R = N * 2.0 * (N * L) - L;
                double r_dot_v = (R * V);
                if (r_dot_v > 0) {
                    intensity = intensity + light.getIntensity() * pow(r_dot_v/(R.magnitude() * V.magnitude()), s);
                }
            }
        }
    }
    return intensity;
}

Vector3D TraceRay(Vector3D cameraOrigin, Vector3D D, double t_min, int t_max, int recursion_depth, Scene scene, Vector3D background_color){

    array<double, 2> closest_ts = ClosestIntersection(cameraOrigin, D, t_min, t_max, scene);
    double closest_object_index = closest_ts[0];
    Primitive closest_object = scene.getObjects()[closest_object_index];

    double closest_t = closest_ts[1];
    if (closest_object_index == -1) {
        return background_color;
    }

    // Return the color of the closest sphere
    Vector3D P = cameraOrigin + (D * closest_t);  // Compute intersection

    Vector3D N = P - closest_object.getCenter();  // Compute sphere normal at intersection
    N = N / N.magnitude();
    Vector3D local_color = closest_object.getColor() * ComputeLighting(P, N, (D*-1), closest_object.getSpecular(), scene);

    // If we hit the recursion limit or the object is not reflective, we're done
    double r = closest_object.getReflective();
    if (recursion_depth <= 0 || r <= 0.0){
        return local_color;
    }
    
    Vector3D R = reflectRay((D*-1), N); // Computer the reflected color
    
    Vector3D reflected_color = TraceRay(P, R, 0.001, 2147483647, recursion_depth - 1, scene, background_color);
    return local_color * (1 - r) + reflected_color * r;

}

Vector3D CanvasToViewport(double x, double y, int ViewportWidth, int ViewportHeight, int CanvasWidth, int CanvasHeight, int distance_viewport_camera){
    Vector3D result = Vector3D(x*ViewportWidth/CanvasWidth, y*ViewportHeight/CanvasHeight, distance_viewport_camera);
    return result;
}

