#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "utils.h"
#include "PathFinder.h"

class ScenePathFinding :
	public Scene
{
public:
	ScenePathFinding();
	~ScenePathFinding();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:

	pathFindingType pathType;
	pairs coinPoints[10];

	std::vector<Agent*> agents;
	Vector2D coinPosition;

	//Variables to find minMax and mitja
	int minV;
	int maxV;
	int mediumV;
	int aux;

	Grid* maze;
	bool draw_grid;
	int counter;
	int counterPaths;
	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
