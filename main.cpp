#include <iostream>
#include <GL\glew.h>
#include "display.h"
#include "shader.h"
#include <SDL2\SDL.h>
#undef main

using namespace std;

int main(int argc, char** argv) {
	Display display(800, 600, "Hello World");
	Shader shader("./res/basicShader");
	cout << "Hello World" << endl;
	bool isRunning = true;
	display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	return 0;
}
