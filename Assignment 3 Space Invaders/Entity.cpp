#include "Entity.h"

Entity::Entity(GLuint textureID, float u, float v, float width, float height, float scale)
:textureID(textureID), u(u), v(v), width(width), height(height), scale(scale), alive(true), d_x(0.1f), d_y(0.04f), shot(false), waittime(-999.0f){};

void Entity::draw(float stretch) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glScalef(stretch, 1.0f, 1.0f);

	GLfloat quad[] = { -width * scale, height * scale, -width * scale, -height * scale,
		width * scale, -height * scale, width * scale, height * scale };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Entity::render(){
	if (alive == true){
		draw();
	}
}