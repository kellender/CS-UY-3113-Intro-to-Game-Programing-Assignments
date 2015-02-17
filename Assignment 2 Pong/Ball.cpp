#include "Ball.h"

Ball::Ball(float x, float y, float height, float width)	:x(x), y(y),width(width), height(height), xVelocity(0.0f), yVelocity(0.0f),
	xAcceleration(0.0f), yAcceleration(0.0f){

}


void Ball::Update(float timeElapsed){
	//distance = velocity * time
	x += xVelocity * timeElapsed;
	y += yVelocity * timeElapsed;


	//velocity = acclaration * time
	xVelocity += xAcceleration * timeElapsed;
	yVelocity += yAcceleration * timeElapsed;


}


void Ball::Draw(){

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(1.0, 1.0, 1.0);

	GLfloat square[] = { -width / 4, height / 4, -width / 4, -height / 4, width / 4, -height / 4, width / 4, height / 4};
	glVertexPointer(2, GL_FLOAT, 0, square);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);

}

const std::array<float, 4>& Ball::hitBox()const{
	std::array<float, 4> stuff = { x, y, width, height };
	return stuff;
}

//Play around
void Ball::hitTopScren(){
	yVelocity = -abs(yVelocity);
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}

void Ball::hitBottomScren(){
	yVelocity = abs(yVelocity);
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}

void Ball::hitLeftScren(float hitAngle, float spin){
	xVelocity = 1.5f;
	yVelocity = 1.5f*pow(abs(hitAngle), 0.5f)*hitAngle;
	xAcceleration = -0.4f * abs(spin);
	yAcceleration = 4.0f * spin;
}

void Ball::hitRightScren(float hitAngle, float spin){
	xVelocity = -1.5f;
	yVelocity = 1.5f*pow(abs(hitAngle), 0.5f)*hitAngle;
	xAcceleration = 0.4f * abs(spin);
	yAcceleration = 4.0f * spin;
}

void Ball::reset(){
	x = 0.0f;
	y = 0.0f;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}