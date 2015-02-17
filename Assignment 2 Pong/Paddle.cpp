#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height):
	x(x), y(y), width(width), height(height), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.0f), yAcceleration(0.0f){}

void Paddle::Update(float timeElapsed){
	y += yVelocity * timeElapsed;
	yAcceleration *= 0.99;
}

void Paddle::Draw(){

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(1.0, 1.0, 1.0);

	GLfloat square[] = { -width / 4, height / 2, -width / 4, -height / 2, width / 4, -height / 2, width / 4, height / 2 };
	glVertexPointer(2, GL_FLOAT, 0, square);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);

}


const std::array<float, 4>& Paddle::hitBox() const{
	std::array<float, 4> stuff = { x, y, width, height };
	return stuff;
}

void Paddle::Up(){
	yVelocity = 1.5f;
	if (yAcceleration == 0.0f){
		yAcceleration = -1.0f;
	}
}

void Paddle::Down(){
	yVelocity = -1.5f;
	if (yAcceleration == 0.0f){
		yAcceleration = 1.0f;
	}
}

void Paddle::Stop(){
	yAcceleration = 0.0f;
	if (yVelocity != 0.0f){
		if (y > 1.0f - height / 2){
			y = 1.0f - height / 2;
		}
		else if (y < -1.0f + height / 2){
			y = -1.0f + height / 2;
		}
		yVelocity = 0.0f;
	}
}

float Paddle::getSpin() const{
	return yAcceleration;
}