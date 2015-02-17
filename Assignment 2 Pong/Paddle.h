#ifndef PADDLE_H
#define PADDLE_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>

using std::array;

class Paddle{
public:
	Paddle(float x, float y, float width, float height);


	void Update(float elapsed);
	void Draw();

	void Up();
	void Down();
	void Stop();
	float getSpin() const;

	const array<float, 4>& hitBox() const;

private:
	float x;
	float y;

	float width;
	float height;

	float xVelocity;
	float yVelocity;

	float xAcceleration;
	float yAcceleration;
};

#endif