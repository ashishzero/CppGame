# CppGame
This is a simple library for rendering and simulation in 2D. CppGame also has a nice banner.
![CppGameBanner](Banner.png)

# Usage

## Using Source

* Just include the source code (`src/CppGame.cpp`) and put the header files (`CppGame.h` and `CppGameCore.h`) in your project
* Include the `CppGame.h` in your code and that's it!!

## Using Static Library

* The build in libraries are found in `bin` directory
* Statically link the library and copy the header files (`CppGame.h` and `CppGameCore.h`) in your project
* Include the `CppGame.h` in your code and that's it!!

# Skeleton Code
This will help you getting started
```cpp
#include "CppGame.h"

// The `Platform` structs holds various data such as Window Size, Input, User Pointer
// User can use `Platform::Scratch` as a scratch buffer for temporary allocation, every frame
// the scratch buffer will be automatically be reset
// The default allocation of scratch is 32 Megabytes

struct MyData {
	float x, y;
};

void FixedUpdate(Platform *p, float dt) {
	// This is fixed timestep simulation function (framerate independent)
	// Perform critical simulations here
	// Simulations performed will be consistent
}

void UpdateAndRender(Platform *p, float dt, float alpha) {
	// This function is not framerate independent, so the simulations done in this function will not be consistent
	// Exit if Escape is pressed
	if (KeyIsPressed(p, KeyEscape)) {
		PlatformQuit(p);
	}

	// Mouse: p->Mouse.Position
	// Mouse Button: ButtonIsDown, ButtonIsPressed, etc
	// For more details check `CppGame.h` header file

	// Clear the background with this color,
	// this is not immediate function, the actual clearing call will be done later
	SetClearColor(.2f, .2f, .2f, 1);

	BeginScene2D(0, p->RenderTargetWidth, 0, p->RenderTargetHeight);

	// DrawLine, DrawQuad, DrawRect, etc (check `CppGame.h` header file for all functions available)

	EndScene2D();
}

// This function gets called by the Library so that you can set up the library
CppGameCall void CppGameInitialize(Platform *platform, int argc, char **argv) {
	platform->Name = "Example Program"; // set your program name
	platform->FixedUpdate = FixedUpdate; // the given function will be called during simulation loop for fixed update
	platform->UpdateAndRender = UpdateAndRender; // the given function will be called during simulation loop for framerate dependent update

	// you can also set callback for function that gets called when window is resized
	// platform->OnWindowResize = MyResizeCallback

	// you can alloc your required data here and set it to the user pointer
	MyData *data = (MyData *)platform->Alloc(sizeof(MyData));
	// initialize with default values
	data->x = 0;
	data->y = 1;

	// Set the user pointer so other functions can access the data
	platform->UserPointer = data;
}
```

# Documentation
Currently the written documentation is not available, but you can check out the list of structs and
functions available in `CppGame.h` file
