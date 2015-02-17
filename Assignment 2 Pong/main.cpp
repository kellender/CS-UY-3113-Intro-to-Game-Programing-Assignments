//i tryed to base it on this game as much as possible: http://www.ponggame.org/

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>
#include <math.h>

#include "Ball.h"
#include "Paddle.h"


#define ORTHOTOP 1.0f
#define ORTHOBOT -1.0f
#define ORTHOLEFT -1.33f
#define ORTHORIGHT 1.33f

using std::array;

SDL_Window* displayWindow;

Ball* ball;
Paddle* paddle;
Paddle* paddle2;

float lastFrameTicks;


int playerOneScore;
int playerTwoScore;

bool newGame;


float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

bool collided(const std::array<float, 4> &rectangle1, const std::array<float, 4> &rectangle2){
	return (abs(rectangle1[0] - rectangle2[0]) <= (rectangle1[2] + rectangle2[2]) / 2 &&
		abs(rectangle1[1] - rectangle2[1]) <= (rectangle1[3] + rectangle2[3]) / 2);
}

void HandleCollisions(){
	const array<float, 4> boxBall = ball->hitBox();
	const array<float, 4> boxPlayer1 = paddle->hitBox();
	const array<float, 4> boxPlayer2 = paddle2->hitBox();

	//Top
	if (boxBall[1] + boxBall[3] / 2 >= ORTHOTOP){
		ball->hitTopScren();
	}
	if (boxPlayer1[1] + boxPlayer1[3] / 2 > ORTHOTOP){
		paddle->Stop();
	}
	if (boxPlayer2[1] + boxPlayer2[3] / 2 > ORTHOTOP){
		paddle2->Stop();
	}

	//Bottom
	if (boxBall[1] - boxBall[3] / 2 <= ORTHOBOT){
		ball->hitBottomScren();
	}
	if (boxPlayer1[1] - boxPlayer1[3] / 2 < ORTHOBOT){
		paddle->Stop();
	}
	if (boxPlayer2[1] - boxPlayer2[3] / 2 < ORTHOBOT){
		paddle2->Stop();
	}

	//Right
	if (boxBall[0] - boxBall[2] / 2 >= ORTHORIGHT){
		playerOneScore++;
		ball->reset();
		ball->hitLeftScren(RandomFloat(-0.7f, 0.7f), RandomFloat(-0.7f, 0.7f));;
	}

	//Left
	if (boxBall[0] + boxBall[2] / 2 <= ORTHOLEFT){
		playerTwoScore++;
		ball->reset();
		ball->hitRightScren(RandomFloat(-0.7f, 0.7f), RandomFloat(-0.7f, 0.7f));
	}
	//Paddle 1
	if (collided(boxBall,boxPlayer1)){
		ball->hitLeftScren((boxBall[1] - boxPlayer1[1]) / (boxPlayer1[3] / 2), paddle->getSpin());
	}

	//Paddle 2
	if (collided(boxBall, boxPlayer2)){
		ball->hitRightScren((boxBall[1] - boxPlayer2[1]) / (boxPlayer2[3] / 2), paddle2->getSpin());
	}
}

void Setup(){
	//Setup SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	displayWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	//Setup OpenGL
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	//set up our project matrix
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);

	
	//background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //black


	//Setup my entities here!

	ball = new Ball(0.0f, 0.0f, 0.1f, 0.1f);
	paddle = new Paddle(-1.18f, 0.0f, 0.1f, 0.30f);
	paddle2 = new Paddle(1.18f, 0.0f, 0.1f, 0.30f);

	lastFrameTicks = 0.0f;

	playerOneScore = 0;
	playerTwoScore = 0;

	newGame = true;

}

void ProcessEvents(bool& done){
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		//Exit
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}

		//Keyboard 2 players ONLY
		else if (event.type == SDL_KEYDOWN){
			//Player 1
			if (event.key.keysym.scancode == SDL_SCANCODE_W){
				paddle->Up();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S){
				paddle->Down();
			}

			//Player 2
			if (event.key.keysym.scancode == SDL_SCANCODE_UP){
				paddle2->Up();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
				paddle2->Down();
			}
		}

		else if (event.type == SDL_KEYUP){
			//Player 1
			if (event.key.keysym.scancode == SDL_SCANCODE_W){
				paddle->Stop();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S){
				paddle->Stop();
			}
			
			//Player 2
			if (event.key.keysym.scancode == SDL_SCANCODE_UP){
				paddle2->Stop();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
				paddle2->Stop();
			}
		}
	}
}

void Update(){
	//Physics

	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	ball->Update(elapsed);
	paddle->Update(elapsed);
	paddle2->Update(elapsed);

	if (newGame){
		ball->hitRightScren(RandomFloat(-0.7f, 0.7f), RandomFloat(-0.7f, 0.7f));
		newGame = false;
	}

	//Collisions
	HandleCollisions();

}

void Render(){
	//Clears the screen to the set color
	glClear(GL_COLOR_BUFFER_BIT);

	//Setup Transforms Draw 
	ball->Draw();
	paddle->Draw();
	paddle2->Draw();

	SDL_GL_SwapWindow(displayWindow);
}


int main(int argc, char *argv[]){
	Setup();
	bool done = false;
	while (!done) {
		ProcessEvents(done);
		Update();
		Render();
	}
	SDL_Quit();
	return 0;
}