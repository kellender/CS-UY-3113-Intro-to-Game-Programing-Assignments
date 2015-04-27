#pragma once
#include "include.h"
#include "Matrix.h"
#include "Vector.h"


class Entity{
public:
	void draw();
	void render();

	GLuint textureID;

	float u;
	float v;
	float scalex;
	float scaley;

	float scalex2;
	float scaley2;

	float rotation;

	float x;
	float y;

	float left;
	float right;
	float top;
	float bottom;

	float speed;
	void updateVector();

	Vector topleft;
	Vector topright;
	Vector bottomleft;
	Vector bottomright;

	float width;
	float height;

	Matrix matrix;
	Matrix inverse;
	void genMatrix();

	void setVector();
	void randomize();
	bool collision(Entity a);

	Vector vector;

	Entity(){};
	Entity(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley)
		:textureID(textureID), u(u), v(v), width(width), height(height), scalex(scalex), scaley(scaley), scalex2(1.0f), scaley2(1.0f), rotation(0.0f){
		left = -width * scalex;
		right = width * scalex;
		top = height * scaley;
		bottom = -height * scaley;
		topleft = Vector(left, top, 1.0f);
		topright = Vector(right, top, 1.0f);
		bottomleft = Vector(left, bottom, 1.0f);
		bottomright = Vector(right, bottom, 1.0f);
	};
};
