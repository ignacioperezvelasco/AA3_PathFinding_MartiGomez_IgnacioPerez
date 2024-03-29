#pragma once
#include <deque>
#include <map>
#include <utility>
#include "Grid.h"
#include "Agent.h"

struct pairs
{
	int NumColumn;
	int NumRow;
};

struct node 
{
	int NumColumn;
	int NumRow;
	pairs came_from;
	int costTill;
};

int BFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
int GBFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
int DIJKSTRAFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
int ASTARFunction(Agent* myAgent, pairs myUbi, Grid* myGrid, Vector2D coinPosition);
void findNeighbors(pairs ubication, pairs* neighborhood, int maxX, int maxY, Grid* myGrid);
void addPath(Agent* myAgent, std::vector<node> visitedNodes, Grid* myGrid);
node getLowestCostTill(std::deque<node> frontier);
int getCostBetweenNodes(pairs nodeA, pairs nodeB, Grid* myGrid);
int myHeuristic(pairs nodeA, pairs nodeB);