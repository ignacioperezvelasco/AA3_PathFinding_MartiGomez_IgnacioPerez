#include "PathFinder.h"

void BFSFunction(Agent* myAgent,Grid* myGrid, Vector2D coinPosition)
{
	/*
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 8)));
	*/
	std::queue<node> frontier;
	std::vector<pair> visited;

	//push first pos
	frontier.push(node{ true,(int) myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pair{-1,-1} });
	node current;

	pair neighBors[4]; 

	findNeighbors(pair{ 5,5 }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY());

	for (int i = 0; i < 4; i++)
	{
		std::cout << (neighBors + i)->NumRow << (neighBors + i)->NumColumn << std::endl;
	}

	while (!frontier.empty())
	{
		current = frontier.front();
		//Check neighbors

		
	}



}

void GBFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 8)));
}

void DIJKSTRAFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 8)));
}

void ASTARFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 8)));
}

void findNeighbors(pair ubication, pair* neighborhood, int maxX, int maxY)
{
	//Vecino izq
	if (ubication.NumColumn -1 > 0)
	{
		neighborhood[0] = pair{ ubication.NumColumn - 1 ,ubication.NumRow};
	}
	else
	{
		neighborhood[0] = pair{- 1 ,-1};
	}
	//vecino derech
	if (ubication.NumColumn +1 < maxX)
	{
		neighborhood[1] = pair{ ubication.NumColumn + 1 , ubication.NumRow };
	}
	else
	{
		neighborhood[1] = pair{ -1 ,-1 };
	}
	//vecino arriba
	if (ubication.NumRow - 1 > 0)
	{
		neighborhood[2] = pair{ ubication.NumColumn  , ubication.NumRow - 1 };
	}
	else
	{
		neighborhood[2] = pair{ -1 ,-1 };
	}
	//vecino abajo
	if (ubication.NumRow + 1 < maxY)
	{
		neighborhood[3] = pair{ ubication.NumColumn  , ubication.NumRow + 1 };
	}
	else
	{
		neighborhood[3] = pair{ -1 ,-1 };
	}
}