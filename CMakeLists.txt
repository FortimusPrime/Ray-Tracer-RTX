# cmake_minimum_required(VERSION 3.10)

# project(ray_tracer_CUDA)

# set(CMAKE_C_STANDARD 99)

# add_executable(${CMAKE_PROJECT_NAME} 
# Source_Code/AnimationMain.cpp 
# Linear_Algebra/linearAlgebraFunctions.cpp 
# Linear_Algebra/Vector3D.cpp 
# Linear_Algebra/Matrix3D.cpp 
# Objects/derivedObjects.cpp 
# Objects/Light.cpp 
# Objects/Primitive.cpp 
# Objects/Scene.cpp 
# Ray-Tracing/RayTracingFunctions.cpp)

# cmake_minimum_required(VERSION 3.10)
# # 
# # Enable CUDA
# project(ray_tracer_CUDA LANGUAGES CXX CUDA)
# # 
# # Detect CUDA architectures or set manually
# # TODO
# set(CMAKE_CUDA_ARCHITECTURES 50 60 70 75 80)  # Adjust for your GPU TODO
# # 
# # Add the executable
# add_executable(${CMAKE_PROJECT_NAME} 
# Source_Code/AnimationMain.cpp 
# Linear_Algebra/linearAlgebraFunctions.cpp 
# Linear_Algebra/Vector3D.cpp 
# Linear_Algebra/Matrix3D.cpp 
# Objects/derivedObjects.cpp 
# Objects/Light.cpp 
# Objects/Primitive.cpp 
# Objects/Scene.cpp 
# Ray-Tracing/RayTracingFunctions.cpp)
# # 
# # Ensure CUDA as the language for the target
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES 
#     CUDA_SEPARABLE_COMPILATION ON
#     CXX_STANDARD 14
# )
# # **Enable OpenMP**
# find_package(OpenMP REQUIRED)
# if(OpenMP_CXX_FOUND)
#     target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
#     target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
# endif()


cmake_minimum_required(VERSION 3.10)

# Enable CUDA
project(ray_tracer_CUDA LANGUAGES CXX CUDA)

# Detect CUDA architectures or set manually
set(CMAKE_CUDA_ARCHITECTURES 50 60 70 75 80)  # Adjust for your GPU

# Find OpenMP
find_package(OpenMP REQUIRED)

# Add the executable
add_executable(${CMAKE_PROJECT_NAME} 
    Source_Code/AnimationMain.cpp 
    Linear_Algebra/linearAlgebraFunctions.cpp 
    Linear_Algebra/Vector3D.cpp 
    Linear_Algebra/Matrix3D.cpp 
    Objects/derivedObjects.cpp 
    Objects/Light.cpp 
    Objects/Primitive.cpp 
    Objects/Scene.cpp 
    Ray-Tracing/RayTracingFunctions.cpp
)

# Ensure CUDA as the language for the target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES 
    CUDA_SEPARABLE_COMPILATION ON
    CXX_STANDARD 14
)

# **Manually Add OpenMP Flags Instead of OpenMP::OpenMP_CXX**
if(OpenMP_CXX_FOUND)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OpenMP_CXX_LIBRARIES})
endif()
