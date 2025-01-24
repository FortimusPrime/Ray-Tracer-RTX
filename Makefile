# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# List of source files and object files
SRC = Source_Code/AnimationMain.cpp \
      Linear_Algebra/linearAlgebraFunctions.cpp \
      Linear_Algebra/Vector3D.cpp \
      Linear_Algebra/Matrix3D.cpp \
      Objects/derivedObjects.cpp \
      Objects/Light.cpp \
      Objects/Primitive.cpp \
      Objects/Scene.cpp \
      Ray-Tracing/RayTracingFunctions.cpp

OBJ = $(SRC:.cpp=.o)

# Target executable
animation_program: $(OBJ)
	$(CXX) $(CXXFLAGS) -o animation_program $(OBJ)
	rm -f *.o
	rm -f */*.o

# Rule to compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f */*.o
