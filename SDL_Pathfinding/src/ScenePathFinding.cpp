#include "ScenePathFinding.h"

using namespace std;

ScenePathFinding::ScenePathFinding():
	pathType(NONE)
{
	draw_grid = true;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent* agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(Vector2D(3,8)));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
	{
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		std::cout << "I'm in bitch" << std::endl;
	}

}

ScenePathFinding::~ScenePathFinding()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFinding::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */

	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		if (event->key.keysym.scancode == SDL_SCANCODE_B) {
			pathType = BFS;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_G)
			pathType = GBFS;
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
			pathType = ASTAR;
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
			pathType = DIJKSTRA;
		break;
	default:
		break;
	}
	
	if (!agents[0]->pathDefined)
	{
		switch (pathType)
		{
		case BFS:
			cout << "BFS" << endl;
			BFSFunction(agents[0], maze, coinPosition);
			agents[0]->pathDefined = true;
			break;
		case DIJKSTRA:
			cout << "DIJKSTRA" << endl;
			DIJKSTRAFunction(agents[0], maze, coinPosition);
			agents[0]->pathDefined = true;
			break;
		case GBFS:
			cout << "GBFS" << endl;
			GBFSFunction(agents[0], maze, coinPosition);
			agents[0]->pathDefined = true;
			break;
		case ASTAR:
			cout << "ASTAR" << endl;
			ASTARFunction(agents[0], maze, coinPosition);
			agents[0]->pathDefined = true;
			break;
		case NONE:
			break;
		default:
			break;
		}
	}

	agents[0]->update(dtime, event);
	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		agents[0]->pathDefined = false;
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
	
}

void ScenePathFinding::draw()
{
	drawMaze();
	drawCoin();
	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
}

const char* ScenePathFinding::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFinding::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)j, (float)i)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
			}
			else {
				// Do not draw if it is not necessary (bg is already black)
			}

			coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
			rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);

		}
	}
	//Alternative: render a backgroud texture:
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL);
}

void ScenePathFinding::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

bool ScenePathFinding::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
