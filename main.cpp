#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"

void pause();

int main(int argc, char** argv) {
	Display display(800, 600, "Hello World");
	Shader shader("./res/basicShader");
	return 0;
}

void pause() {
	std::cout << std::endl << "Press any key to continue...";
	getchar();
}