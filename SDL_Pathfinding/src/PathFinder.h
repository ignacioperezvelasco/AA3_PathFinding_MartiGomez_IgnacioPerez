#pragma once
#include <queue>
#include <utility>
#include "Grid.h"
#include "Agent.h"

struct pair
{
	int NumRow;
	int NumColumn;
};

struct node 
{
	bool transitable;
	int NumRow;
	int NumColumn;
	pair came_from;
};

void BFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void GBFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void DIJKSTRAFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
void ASTARFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition);
