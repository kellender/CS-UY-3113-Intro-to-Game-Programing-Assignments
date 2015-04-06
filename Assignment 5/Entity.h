#include "GameState.h"



class Entity{
public:
	void draw(int frame);
	void render();

	GLuint textureID;

	void resetcollision();

	bool collisionx(Entity entity);
	bool collisiony(Entity entity);
	bool collision(Entity entity);

	vector<float> u;
	vector<float> v;
	float scale;
	bool faceleft;

	float x;
	float y;
	float x_pen;
	float y_pen;
	bool active;

	int gridx;
	int gridy;

	float elapsed;
	int frame;

	float width;
	float height;

	float v_x;
	float v_y;

	float a_x;
	float a_y;

	float f_x;
	float f_y;

	bool alive;
	bool dynamic;

	bool collidedTop;
	bool collidedBottom;
	bool collidedRight;
	bool collidedLeft;

	Entity(){};
	Entity(GLuint textureID0, float u0, float v0, float width, float height, float scale, bool dynamic, bool alive);
};