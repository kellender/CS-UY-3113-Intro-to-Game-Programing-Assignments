#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#ifndef BULLET_H
#define BULLET_H

class Bullet{
public:
	void draw();
	void update();
	float u;
	float v;
	float width;
	float height;
	float scale;

	float x;
	float y;
	float speed;

	GLuint textureID;

	bool visible;
	float timeAlive;

	Bullet(){};
	Bullet(GLuint textureID, float u, float v, float width, float height, float scale, float x, float y, bool visible);
};
#endif