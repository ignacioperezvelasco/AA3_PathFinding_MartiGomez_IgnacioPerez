#include "PathFinder.h"

void BFSFunction(Agent* myAgent,Grid* myGrid) 
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(5, 8)));
}
void GBFSFunction(Agent* myAgent, Grid* myGrid)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(10, 8)));
}
void DIJKSTRAFunction(Agent* myAgent, Grid* myGrid)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(14, 8)));
}
void ASTARFunction(Agent* myAgent, Grid* myGrid)
{
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 4)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 5)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 6)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 7)));
	myAgent->addPathPoint(myGrid->cell2pix(Vector2D(18, 8)));
}