#include <iostream>
#include <GL\glew.h>
#include "display.h"
#include "shader.h"
#include <SDL2/SDL.h>
#undef main

using namespace std;

int main(int argc, char** argv) {
	Display display(1366, 768, "OpenGL Window");
	while (!display.isClosed()) {
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);
		display.update();
	}
	return 0;
}
