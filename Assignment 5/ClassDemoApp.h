#include "GameState.h"
#include "Entity.h"


class Plat{
public:
	Plat();
	~Plat();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update();
	
private:
	unsigned char **levelData;

	void genLevel();
	vector<float> vertexData;
	vector<float> texCoordData;
	void freeLevel();

	void buildLevel(unsigned char **newlevelData, int levelheight, int levelwidth);

	bool collisionx(Entity&entity);
	bool collisiony(Entity&entity);

	float world_offset_x;
	float world_offset_y;
	int levelheight;
	int levelwidth;
	int jumped;
	int enemyCount;
	void createEnemy();
	const Uint8* keys;
	bool done;
	float animation;
	GameState state;
	float lastFrameTicks;

	GLuint font;
	GLuint sprites;
	void worldtoTileCoordinates(float x, float y, int &gridx, int &gridy);
	void tiletoWorldCoordinatesx(float &x, int gridx);
	void tiletoWorldCoordinatesy(float &y, int gridy);

	Entity blocks[10];
	Entity enemy[TOTAL_ENEMIES];
	Entity prize[TOTAL_PRIZES];
	int enemysize;
	float gravity;

	void reset();

	void RenderMainMenu();
	void RenderGameLevel();
	void RenderGameOver();

	void UpdateGameLevel();

	bool bumprightwall();
	bool bumpleftwall();
	float delay;
	Entity user;

	int score;
};