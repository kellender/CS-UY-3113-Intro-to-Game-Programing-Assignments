#ifndef BALL_H
#define BALL_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>
#include <math.h>

using std::array;

class Ball{
public:
	Ball(float x, float y, float height, float width);


	void Update(float elapsed);
	void Draw();

	const array<float, 4>& hitBox() const;
	void hitTopScren();
	void hitBottomScren();
	void hitLeftScren(float hitAngle, float spin);
	void hitRightScren(float hitAngle, float spin);
	void reset();

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