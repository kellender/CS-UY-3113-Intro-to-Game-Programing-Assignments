#include "ClassDemoApp.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;




GLuint LoadTexture(const char *image_path, GLenum format) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void drText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;
	for (unsigned int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;

		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		vertexData.insert(vertexData.end(), { ((size + spacing) * i) + (-0.5f * size), 0.5f * size, ((size + spacing) * i) +
			(-0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), 0.5f
			* size });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
			texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}
	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, text.size() * 4);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

bool SpInvd::eachuserhit(Entity enemy){
	if (((enemy.bullet.x + enemy.bullet.width*enemy.bullet.scale<user.x - user.width*user.scale) || (enemy.bullet.x - enemy.bullet.width*enemy.bullet.scale>user.x + user.width*user.scale) ||
		(enemy.bullet.y + enemy.bullet.height*enemy.bullet.scale<user.y - user.height*user.scale) || (enemy.bullet.y - enemy.bullet.height*enemy.bullet.scale>user.y + user.height*user.scale)) &&
		((enemy.bullet.x + enemy.bullet.width*enemy.bullet.scale<user.x - user.width*user.scale) || (enemy.bullet.x - enemy.bullet.width*enemy.bullet.scale>user.x + user.width*user.scale) ||
		(enemy.bullet.y + enemy.bullet.height*enemy.bullet.scale<user.y - user.height*user.scale) || (enemy.bullet.y - enemy.bullet.height*enemy.bullet.scale>user.y + user.height*user.scale))){
		return false;
	}
	return true;
}

bool SpInvd::enemyhit(Entity enemy){
	if (((user.bullet.x + user.bullet.width*user.bullet.scale<enemy.x - enemy.width*enemy.scale) || (user.bullet.x - user.bullet.width*user.bullet.scale>enemy.x + enemy.width*enemy.scale) ||
		(user.bullet.y + user.bullet.height*user.bullet.scale<enemy.y - enemy.height*enemy.scale) || (user.bullet.y - user.bullet.height*user.bullet.scale>enemy.y + enemy.height*enemy.scale)) &&
		((user.bullet.x + user.bullet.width*user.bullet.scale<enemy.x - enemy.width*enemy.scale) || (user.bullet.x - user.bullet.width*user.bullet.scale>enemy.x + enemy.width*enemy.scale) ||
		(user.bullet.y + user.bullet.height*user.bullet.scale<enemy.y - enemy.height*enemy.scale) || (user.bullet.y - user.bullet.height*user.bullet.scale>enemy.y + enemy.height*enemy.scale))){
		return false;
	}
	return true;
}

bool SpInvd::userhit(){
	bool hit = false;
	for (int i = 0; i < numEnemy; i++){
		hit = hit || (eachuserhit(enemyOne[i]) || eachuserhit(enemyTwo[i]) || eachuserhit(enemyThree[i]) || eachuserhit(enemyFour[i]));
		if (hit) {
			return true;
		}
	}
	return false;
}

bool SpInvd::bumpleftwall(){
	for (int i = 0; i < numEnemy; i++){
		if (enemyOne[i].alive || enemyTwo[i].alive || enemyThree[i].alive || enemyFour[i].alive){
			if (min(min(enemyOne[i].x, enemyTwo[i].x), min(enemyThree[i].x, enemyFour[i].x)) - enemyTwo[i].width*enemyOne[i].scale < -1.33f){
				return true;
			}
		}
	}
	return false;
}

bool SpInvd::bumprightwall(){
	for (int i = 0; i < numEnemy; i++){
		if (enemyOne[i].alive || enemyTwo[i].alive || enemyThree[i].alive || enemyFour[i].alive){
			if (max(max(enemyOne[i].x, enemyTwo[i].x), max(enemyThree[i].x, enemyFour[i].x)) + enemyOne[i].width*enemyOne[i].scale > 1.33f){
				return true;
			}
		}
	}
	return false;
}

void SpInvd::reset(){
	score = 0;
	lives = 3;
	delay = 0.0f;

	GLuint SheetSpriteTexture = LoadTexture("sheet.png", GL_RGBA);
	fill_n(enemyOne, numEnemy, Entity(SheetSpriteTexture, 425.0f / 1024.0f, 468.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.7f));
	fill_n(enemyTwo, numEnemy, Entity(SheetSpriteTexture, 423.0f / 1024.0f, 728.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.7f));
	fill_n(enemyThree, numEnemy, Entity(SheetSpriteTexture, 425.0f / 1024.0f, 552.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.7f));
	fill_n(enemyFour, numEnemy, Entity(SheetSpriteTexture, 425.0f / 1024.0f, 384.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.7f));

	float xtemp = -1.15f;
	float ytemp = 0.6f;

	for (int i = 0; i < numEnemy; i++){
		enemyOne[i].x = xtemp;
		enemyOne[i].y = ytemp;
		enemyOne[i].bullet = Bullet(SheetSpriteTexture, 856.0f / 1024.0f, 812.0f / 1024.0f, 9.0f / 1024.0f, 57.0f / 1024.0f, 0.6f, xtemp, ytemp, true);
		enemyTwo[i].x = xtemp;
		enemyTwo[i].y = ytemp - 0.18f;
		enemyTwo[i].bullet = Bullet(SheetSpriteTexture, 856.0f / 1024.0f, 812.0f / 1024.0f, 9.0f / 1024.0f, 57.0f / 1024.0f, 0.6f, xtemp, ytemp - 0.18f, true);
		enemyThree[i].x = xtemp;
		enemyThree[i].y = ytemp - 0.36f;
		enemyThree[i].bullet = Bullet(SheetSpriteTexture, 856.0f / 1024.0f, 812.0f / 1024.0f, 9.0f / 1024.0f, 57.0f / 1024.0f, 0.6f, xtemp, ytemp - 0.36f, true);
		enemyFour[i].x = xtemp;
		enemyFour[i].y = ytemp - 0.54f;
		enemyFour[i].bullet = Bullet(SheetSpriteTexture, 856.0f / 1024.0f, 812.0f / 1024.0f, 9.0f / 1024.0f, 57.0f / 1024.0f, 0.6f, xtemp, ytemp - 0.54f, true);
		xtemp += 0.18f;
	}
	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 1.7f);

	user.x = 0.0f;
	user.y = -0.8f;
	user.bullet = Bullet(SheetSpriteTexture, 855.0f / 1024.0f, 173.0f / 1024.0f, 9.0f / 1024.0f, 57.0f / 1024.0f, 0.6f, user.x, user.y, false);


}

SpInvd::SpInvd() {
	Init();
}

void SpInvd::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Space Invadors", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	keys = SDL_GetKeyboardState(NULL);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);

	state = STATE_MAIN_MENU;

	done = false;
	lastFrameTicks = 0.0f;
	numEnemy = 10;

	font = LoadTexture("font1.png", GL_RGBA);

	glMatrixMode(GL_MODELVIEW);

}

SpInvd::~SpInvd() {
	SDL_Quit();
}

void SpInvd::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	switch (state) {
	case STATE_MAIN_MENU:
		RenderMainMenu();
		break;
	case STATE_GAME_LEVEL:
		RenderGame();
		break;
	case STATE_GAME_OVER:
		RenderGameOver();
		break;
	}
	SDL_GL_SwapWindow(displayWindow);
}

void SpInvd::RenderMainMenu(){
	//drText(font, "SPACE INVADERS", 0.3f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, -0.97f, 0.3f);
	drText(font, "Welcome to Space Invadors", 0.2f, -0.11f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.3f);
	drText(font, "Press SPACE to play!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.93f, -0.6f);
	drText(font, "Keys:left & right arrow keys, space to shoot.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.95f, 0.0f);
	drText(font, "If you run out of lives, or the ships ", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.95f, -0.1f);
	drText(font, "reach font its game is over!!!", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.95f, -0.2f);
}

void SpInvd::RenderGame(){
	drText(font, "Score", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 0.65f, 0.9f);

	if (lives == 3){
		drText(font, "Lives 3", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.8f, 0.9f);
	}
	else if (lives == 2){
		drText(font, "Lives 2", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.8f, 0.9f);
	}
	else if (lives == 1){
		drText(font, "Lives 1", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -0.8f, 0.9f);
	}

	drText(font, to_string(score), 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 0.65f, 0.8f);

	for (int i = 0; i < numEnemy; i++){
		enemyOne[i].render();
		enemyOne[i].bullet.draw();
		enemyTwo[i].render();
		enemyTwo[i].bullet.draw();
		enemyThree[i].render();
		enemyThree[i].bullet.draw();
		enemyFour[i].render();
		enemyFour[i].bullet.draw();
	}

	user.render();
	user.bullet.draw();



}

void SpInvd::RenderGameOver(){
	drText(font, "Final score:", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.8f, 0.45f);
	drText(font, to_string(score), 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.1f, 0.2f);

	drText(font, "SPACE to play again!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.25f, -0.2f);
	drText(font, "ENTER for main menu!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.15f, -0.4f);
}

void SpInvd::Update(float elapsed) {
	if (state == STATE_GAME_LEVEL){
		UpdateGameLevel(elapsed);
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && state == STATE_GAME_LEVEL){
				if (user.bullet.visible == false){
					user.bullet.x = user.x;
					user.bullet.y = user.y;
					user.bullet.visible = true;
				}
			}
			if (state == STATE_GAME_OVER){
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
					state = STATE_MAIN_MENU;
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
					state = STATE_GAME_LEVEL;
					reset();
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && state == STATE_MAIN_MENU){
				state = STATE_GAME_LEVEL;
				reset();
			}
		}
	}
}

void SpInvd::UpdateGameLevel(float elapsed){
	if (lives == 0 || score == 1000){
		state = STATE_GAME_OVER;
		return;
	}


	delay -= elapsed;

	if (user.bullet.visible == true) {
		user.bullet.y += elapsed * 2.0f;
	}

	if (user.bullet.y > 1.2f) {
		user.bullet.visible = false;
	}

	if (userhit()){
		for (int i = 0; i < numEnemy; i++){
			enemyOne[i].bullet.y = -2.0f;
			enemyOne[i].bullet.x = enemyOne[i].x;
			enemyOne[i].shot = false;
			enemyTwo[i].bullet.y = -2.0f;
			enemyTwo[i].bullet.x = enemyTwo[i].x;
			enemyTwo[i].shot = false;
			enemyThree[i].bullet.y = -2.0f;
			enemyThree[i].bullet.x = enemyThree[i].x;
			enemyThree[i].shot = false;
			enemyFour[i].bullet.y = -2.0f;
			enemyFour[i].bullet.x = enemyFour[i].x;
			enemyFour[i].shot = false;

		}
		user.x = 0.0f;
		lives--;
	}

	if (delay < 0.0f) {
		for (int i = 0; i < numEnemy; i++){

			if (bumprightwall() || bumpleftwall()){
				enemyOne[i].d_x = -(enemyOne[i].d_x)*1.15f;
				enemyTwo[i].d_x = -(enemyTwo[i].d_x)*1.15f;
				enemyThree[i].d_x = -(enemyThree[i].d_x)*1.15f;
				enemyFour[i].d_x = -(enemyFour[i].d_x)*1.15f;
				enemyOne[i].y -= enemyOne[i].d_y;
				enemyTwo[i].y -= enemyTwo[i].d_y;
				enemyThree[i].y -= enemyThree[i].d_y;
				enemyFour[i].y -= enemyFour[i].d_y;
				if (!enemyOne[i].shot && enemyOne[i].alive){
					enemyOne[i].bullet.y = enemyOne[i].y;
				}
				if (!enemyTwo[i].shot && enemyTwo[i].alive){
					enemyTwo[i].bullet.y = enemyTwo[i].y;
				}
				if (!enemyThree[i].shot && enemyThree[i].alive){
					enemyThree[i].bullet.y = enemyThree[i].y;
				}
				if (!enemyFour[i].shot && enemyFour[i].alive){
					enemyFour[i].bullet.y = enemyFour[i].y;
				}
			}
		}
		delay = 0.05f;
	}

	for (int i = 0; i < numEnemy; i++){
		if (enemyhit(enemyOne[i]) && enemyOne[i].alive){
			score += 40;
			enemyOne[i].x = 0.0f;
			enemyOne[i].alive = false;
			if (!enemyOne[i].shot){
				enemyOne[i].bullet.visible = false;
			}
			user.bullet.y = 10.0f;
			user.bullet.visible = false;
			break;
		}
		else if (enemyhit(enemyTwo[i]) && enemyTwo[i].alive){
			score += 30;
			enemyTwo[i].x = 0.0f;
			enemyTwo[i].alive = false;
			if (!enemyTwo[i].shot){
				enemyTwo[i].bullet.visible = false;
			}
			user.bullet.y = 10.0f;
			user.bullet.visible = false;
			break;
		}
		else if (enemyhit(enemyThree[i]) && enemyThree[i].alive){
			score += 20;
			enemyThree[i].x = 0.0f;
			enemyThree[i].alive = false;
			if (!enemyThree[i].shot){
				enemyThree[i].bullet.visible = false;
			}
			user.bullet.y = 10.0f;
			user.bullet.visible = false;
			break;
		}
		else if (enemyhit(enemyFour[i]) && enemyFour[i].alive){
			score += 10;
			enemyFour[i].x = 0.0f;
			enemyFour[i].alive = false;
			if (!enemyFour[i].shot){
				enemyFour[i].bullet.visible = false;
			}
			user.bullet.y = 10.0f;
			user.bullet.visible = false;
			break;
		}
	}

	for (int i = 0; i < numEnemy; i++){

		if (!enemyOne[i].alive && enemyOne[i].bullet.y < -2.0f){}
		else {
			if (enemyOne[i].shot){
				enemyOne[i].bullet.y -= enemyOne[i].bullet.speed*elapsed;
			}
			else if (enemyOne[i].alive) {
				enemyOne[i].bullet.x += enemyOne[i].d_x*elapsed;
			}
			else if (enemyOne[i].alive && !enemyOne[i].shot){
				enemyOne[i].bullet.y = -2.0f;
			}
		}

		if (!enemyTwo[i].alive && enemyTwo[i].bullet.y < -2.0f){}
		else {
			if (enemyTwo[i].shot){
				enemyTwo[i].bullet.y -= enemyTwo[i].bullet.speed*elapsed;
			}
			else if (enemyTwo[i].alive){
				enemyTwo[i].bullet.x += enemyTwo[i].d_x*elapsed;
			}
			else if (enemyTwo[i].alive && !enemyTwo[i].shot){
				enemyTwo[i].bullet.y = -2.0f;
			}
		}

		if (!enemyThree[i].alive && enemyThree[i].bullet.y < -2.0f){}
		else {
			if (enemyThree[i].shot){
				enemyThree[i].bullet.y -= enemyThree[i].bullet.speed*elapsed;
			}
			else if (enemyThree[i].alive){
				enemyThree[i].bullet.x += enemyThree[i].d_x*elapsed;
			}
			else if (enemyThree[i].alive && !enemyThree[i].shot){
				enemyThree[i].bullet.y = -2.0f;
			}
		}

		if (!enemyOne[i].alive && enemyOne[i].bullet.y < -2.0f){}
		else {
			if (enemyFour[i].shot){
				enemyFour[i].bullet.y -= enemyFour[i].bullet.speed*elapsed;
			}
			else if (enemyFour[i].alive){
				enemyFour[i].bullet.x += enemyFour[i].d_x*elapsed;
			}
			else if (enemyFour[i].alive && !enemyFour[i].shot){
				enemyFour[i].bullet.y = -2.0f;
			}
		}
		if (enemyOne[i].alive){
			enemyOne[i].waittime -= elapsed;
			enemyOne[i].x += enemyOne[i].d_x*elapsed;
			if (enemyOne[i].waittime < -900.0f) {
				enemyOne[i].waittime = rand() % 12 + 1.0f;
			}
			else if (enemyOne[i].waittime < 0.0f){
				enemyOne[i].shot = true;
				enemyOne[i].waittime = rand() % 12 + 4.0f;
			}
			if (enemyOne[i].bullet.y < -1.5f) {
				enemyOne[i].bullet.x = enemyOne[i].x;
				enemyOne[i].bullet.y = enemyOne[i].y;
				enemyOne[i].shot = false;
			}
		}
		if (enemyTwo[i].alive){
			enemyTwo[i].waittime -= elapsed;
			enemyTwo[i].x += enemyTwo[i].d_x*elapsed;
			if (enemyTwo[i].waittime < -900.0f) {
				enemyTwo[i].waittime = rand() % 12 + 1.0f;
			}
			else if (enemyTwo[i].waittime < 0.0f){
				enemyTwo[i].shot = true;
				enemyTwo[i].waittime = rand() % 12 + 4.0f;
			}
			if (enemyTwo[i].bullet.y < -1.5f) {
				enemyTwo[i].bullet.x = enemyTwo[i].x;
				enemyTwo[i].bullet.y = enemyTwo[i].y;
				enemyTwo[i].shot = false;
			}
		}
		if (enemyThree[i].alive){
			enemyThree[i].waittime -= elapsed;
			enemyThree[i].x += enemyThree[i].d_x*elapsed;
			if (enemyThree[i].waittime < -900.0f) {
				enemyThree[i].waittime = rand() % 12 + 1.0f;
			}
			else if (enemyThree[i].waittime < 0.0f){
				enemyThree[i].shot = true;
				enemyThree[i].waittime = rand() % 12 + 4.0f;
			}
			if (enemyThree[i].bullet.y < -1.5f) {
				enemyThree[i].bullet.x = enemyThree[i].x;
				enemyThree[i].bullet.y = enemyThree[i].y;
				enemyThree[i].shot = false;
			}
		}
		if (enemyFour[i].alive){
			enemyFour[i].waittime -= elapsed;

			enemyFour[i].x += enemyFour[i].d_x*elapsed;
			if (enemyFour[i].waittime < -900.0f) {
				enemyFour[i].waittime = rand() % 12 + 1.0f;
			}
			else if (enemyFour[i].waittime < 0.0f){
				enemyFour[i].shot = true;
				enemyFour[i].waittime = rand() % 12 + 4.0f;
			}
			if (enemyFour[i].bullet.y < -1.5f) {
				enemyFour[i].bullet.x = enemyFour[i].x;
				enemyFour[i].bullet.y = enemyFour[i].y;
				enemyFour[i].shot = false;
			}
		}
	}
	if (keys[SDL_SCANCODE_LEFT]){
		if (user.x - user.width*user.scale > -1.33){
			user.x -= 0.75f * elapsed;
		}
	}
	else if (keys[SDL_SCANCODE_RIGHT]){
		if (user.x + user.width*user.scale < 1.33){
			user.x += 0.75f * elapsed;
		}
	}
}

bool SpInvd::UpdateAndRender() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;
	Update(elapsed);
	Render();
	return done;
}