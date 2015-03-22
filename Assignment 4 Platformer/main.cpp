#include "ClassDemoApp.h"

//too clean
int main(int argc, char *argv[])
{
	Plat Platformer;
	while (!Platformer.UpdateAndRender()) {}
	return 0;
}