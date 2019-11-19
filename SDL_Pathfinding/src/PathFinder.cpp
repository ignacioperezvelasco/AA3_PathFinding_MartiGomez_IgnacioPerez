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
	std::deque<node> frontier;
	std::vector<node> visited;



	//push first pos
	frontier.push_back(node{(int) myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pair{-1,-1} });
	

	std::cout << frontier.front().NumColumn << std::endl;
	//visited.push_back(node{(int)myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pair{-1,-1} });
	node current;

	pair neighBors[4]; 

	bool exists = false;
	bool existsToVisit = false;
	bool earlyExit=false;
	int count = 0;

	while (!frontier.empty())
	{
		count++;
		current = frontier.front();
		//Check neighbors
		findNeighbors(pair{ current.NumColumn,current.NumRow }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY(), myGrid);
		//check neighbors
		for (int i = 0; i < 4; i++)
		{
			//Do the exit if it's node goal////////////////////////////
			if (((neighBors + i)->NumColumn == (int)coinPosition.x) && ((neighBors + i)->NumRow == (int)coinPosition.y))
			{
				std::cout << "found!" << std::endl;
				visited.push_back(current);
				visited.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pair{current.NumColumn,current.NumRow} });
				earlyExit = true;
				break;
			}
			///////////////////////////////////////////////////////////
			
			//checking it exists////////////////////
			if ((neighBors + i)->NumRow != -1)
			{
				//Checking it isn't visited
				if (!visited.empty()) 
				{
					for (auto t = visited.begin(); t != visited.end(); ++t)
					{
						if (((neighBors + i)->NumColumn == t->NumColumn) && ((neighBors + i)->NumRow == t->NumRow))
						{
							exists = true;
						}
					}
				}
				
				if (!exists)
				{
					//Check isn't going to be visited
					for (auto t = frontier.begin(); t != frontier.end(); ++t)
					{
						if (((neighBors + i)->NumColumn == t->NumColumn) && ((neighBors + i)->NumRow == t->NumRow))
						{
							existsToVisit = true;
						}
					}
				}
				//if its not in any queue
				if ((!existsToVisit) && (!exists))
				{
					frontier.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pair {current.NumColumn,current.NumRow} });
					//std::cout << "hace push de la celda [" << (neighBors + i)->NumColumn << "][" << (neighBors + i)->NumRow << "]"<<std::endl;
				}
				//bools to false
				exists = false;
				existsToVisit = false;
			}

		}
		//if we found objective
		if (earlyExit)
		{
			break;
		}
		frontier.pop_front();
		draw_circle(TheApp::Instance()->getRenderer(), (int) (myGrid->cell2pix(Vector2D{(float)current.NumColumn,(float)current.NumRow}).x) , (int)myGrid->cell2pix((Vector2D{ (float)current.NumColumn,(float)current.NumRow })).y, 15, 255, 255, 0, 255);
		visited.push_back(current);
		
	}
	std::cout << count << std::endl;

	//we push the path in the agent 
	addPath(myAgent, visited, myGrid);

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

void findNeighbors(pair ubication, pair* neighborhood, int maxX, int maxY, Grid* myGrid)
{
	//Vecino izq
	if ((ubication.NumColumn -1 > 0) && (myGrid->terrain[ubication.NumRow][ubication.NumColumn - 1] ==1))
	{
		neighborhood[0] = pair{ ubication.NumColumn - 1 ,ubication.NumRow};
	}
	else
	{
		neighborhood[0] = pair{- 1 ,-1};
	}
	//vecino derech
	if ((ubication.NumColumn +1 < maxX) && (myGrid->terrain[ubication.NumRow][ubication.NumColumn + 1] == 1))
	{
		neighborhood[1] = pair{ ubication.NumColumn + 1 , ubication.NumRow };
	}
	else
	{
		neighborhood[1] = pair{ -1 ,-1 };
	}
	//vecino arriba
	if ((ubication.NumRow - 1 > 0) && (myGrid->terrain[ubication.NumRow-1][ubication.NumColumn] == 1))
	{
		neighborhood[2] = pair{ ubication.NumColumn  , ubication.NumRow - 1 };
	}
	else
	{
		neighborhood[2] = pair{ -1 ,-1 };
	}
	//vecino abajo
	if ((ubication.NumRow + 1 < maxY) && (myGrid->terrain[ubication.NumRow + 1][ubication.NumColumn] == 1))
	{
		neighborhood[3] = pair{ ubication.NumColumn  , ubication.NumRow + 1 };
	}
	else
	{
		neighborhood[3] = pair{ -1 ,-1 };
	}
}

void addPath(Agent* myAgent, std::vector<node> visitedNodes, Grid *myGrid)
{
	std::vector<node> finalPath;
	pair toSearch{ visitedNodes.back().NumColumn,visitedNodes.back().NumRow };
	finalPath.push_back(visitedNodes.back());
	//myAgent->addPathPoint(myGrid->cell2pix(Vector2D(t->NumColumn, t->NumRow)));
	while(toSearch.NumColumn!=-1 )
	{
		for (auto t = visitedNodes.begin(); t != visitedNodes.end(); ++t)
		{
			if ((t->NumColumn==toSearch.NumColumn)&&(t->NumRow == toSearch.NumRow))
			{
				finalPath.push_back(node{ t->NumColumn,t->NumRow,t->came_from });
				toSearch = t->came_from;
				break;
			}
		}
	}
	for (std::vector<node>::reverse_iterator i = finalPath.rbegin();	i != finalPath.rend(); ++i)
	{
		myAgent->addPathPoint(myGrid->cell2pix(Vector2D(i->NumColumn, i->NumRow)));
	}
}
