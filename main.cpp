#include <iostream>
#include <GL/glew.h>

void pause();

int main(int argc, char** argv) {
	std::cout << "Hello World!" << std::endl;
	pause();
	return 0;
}

void pause() {
	std::cout << std::endl << "Press any key to continue...";
	getchar();
}