#pragma once
#include "include.h"

class Vector {
public:
	Vector();
	Vector(float a, float b, float c);
	float length();
	void normalize();
	float x;
	float y;
	float z;
};