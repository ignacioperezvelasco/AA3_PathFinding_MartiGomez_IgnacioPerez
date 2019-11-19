#pragma once
#include <deque>
#include <utility>
#include "Grid.h"
#include "Agent.h"

struct pair
{
	int NumColumn;
	int NumRow;
};

struct node 
{
	int NumColumn;
	int NumRow;
	pair came_from;
};


Vector2D cellToPix(Vector2D cell);
void BFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void GBFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void DIJKSTRAFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void ASTARFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void findNeighbors(pair ubication, pair* neighborhood, int maxX, int maxY, Grid* myGrid);
void addPath(Agent* myAgent, std::vector<node> visitedNodes, Grid* myGrid);