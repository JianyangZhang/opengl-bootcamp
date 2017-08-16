#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>

using namespace std;

class Display {
public:
	Display(int width, int height, const string& title);
	void clear(float r, float g, float b, float a);
	void update();
	bool isClosed();
	virtual ~Display();
protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	int INITIAL_POS_X = 25;
	int INITIAL_POS_Y = 50;
};

#endif
