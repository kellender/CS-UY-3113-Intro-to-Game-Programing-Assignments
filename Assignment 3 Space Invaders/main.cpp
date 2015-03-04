#include "ClassDemoApp.h"

//too clean
int main(int argc, char *argv[])
{
	SpInvd SpacInvadors;
	while (!SpacInvadors.UpdateAndRender()) {}
	return 0;
}