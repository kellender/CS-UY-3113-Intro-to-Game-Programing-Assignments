#include "App.h"
#include "Entity.h"
#include "Matrix.h"
#include "Vector.h"
#include "App.h"

SDL_Window* displayWindow;

//back to cleanly ness
int main(int argc, char *argv[])
{

	App app;

	while (!app.UpdateAndRender()){
	}
	return 0;
}