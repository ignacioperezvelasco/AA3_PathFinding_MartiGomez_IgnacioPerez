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
	frontier.push(node{ true, myGrid->cell2pix(myAgent->getPosition()).x, myGrid->cell2pix(myAgent->getPosition()).y, pair{-1,-1} });
	node current;
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