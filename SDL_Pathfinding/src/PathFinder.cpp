#include "PathFinder.h"

int BFSFunction(Agent* myAgent,Grid* myGrid, Vector2D coinPosition)
{
	//Variables/////////////////////////////
	std::deque<node> frontier;
	std::vector<node> visited;
	node current;
	pairs neighBors[4];
	bool exists = false;
	bool existsToVisit = false;
	bool earlyExit = false;
	int count = 0;
	///////////////////////////

	//push first pos
	frontier.push_back(node{(int) myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pairs{-1,-1} });

	while (!frontier.empty())
	{
		
		//actualize current node to search neighbors
		current = frontier.front();
		//Get neighbors
		findNeighbors(pairs{ current.NumColumn,current.NumRow }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY(), myGrid);
		//check neighbors
		for (int i = 0; i < 4; i++)
		{
			//Do the exit if it's node goal////////////////////////////
			if (((neighBors + i)->NumColumn == (int)coinPosition.x) && ((neighBors + i)->NumRow == (int)coinPosition.y))
			{
				//std::cout << "found with BFS!" << std::endl;
				visited.push_back(current);
				visited.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs {current.NumColumn,current.NumRow} });
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
					frontier.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs {current.NumColumn,current.NumRow} });
				}
				//bools to false
				exists = false;
				existsToVisit = false;
			}
			///////////////////////////////////////
		}

		//if we found objective
		if (earlyExit)
		{
			break;
		}

		//Get out node already searched
		frontier.pop_front();
		count++;
		//Push visited node
		visited.push_back(current);
		
	}

	//std::cout << count << std::endl;

	//we push the path in the agent 
	addPath(myAgent, visited, myGrid);
	return count;
}

int GBFSFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition)
{
	//Variables/////////////////////////////
	std::deque<node> frontier;
	std::vector<node> visited;
	node current;
	pairs neighBors[4];
	bool exists = false;
	bool existsToVisit = false;
	bool earlyExit = false;
	int count = 0;
	int indexToErase = -1;
	///////////////////////////

	//push first pos
	frontier.push_back(node{ (int)myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pairs{-1,-1}, myHeuristic(pairs{(int)myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y},pairs{(int)coinPosition.x,(int)coinPosition.y}) });

	while (!frontier.empty())
	{
		//actualize current node to search neighbors
		current = getLowestCostTill(frontier);;
		//Get neighbors
		findNeighbors(pairs{ current.NumColumn,current.NumRow }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY(), myGrid);
		//check neighbors
		for (int i = 0; i < 4; i++)
		{
			//Do the exit if it's node goal////////////////////////////
			if (((neighBors + i)->NumColumn == (int)coinPosition.x) && ((neighBors + i)->NumRow == (int)coinPosition.y))
			{
				visited.push_back(current);
				visited.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs { current.NumColumn,current.NumRow } });
				earlyExit = true;
				break;
			}
			///////////////////////////////////////////////////////////

			//checking it exists/////////////////////////////////////////////////////////////////
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
					frontier.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs { current.NumColumn,current.NumRow }, myHeuristic(pairs{(neighBors + i)->NumColumn,(neighBors + i)->NumRow},pairs{(int)coinPosition.x,(int)coinPosition.y}) });
				}
				//bools to false
				exists = false;
				existsToVisit = false;
			}
			/////////////////////////////////////////////////////////////////////////////////////
		}

		//if we found objective
		if (earlyExit)
		{
			break;
		}
		indexToErase = 0;
		//Get out node already searched
		for (auto t = frontier.begin(); t != frontier.end(); ++t)
		{
			if ((current.NumRow == t->NumRow) && (current.NumColumn == t->NumColumn))
			{
				break;
			}
			else
				indexToErase++;
		}
		frontier.erase(frontier.begin() + indexToErase);
		count++;
		//Push visited node
		visited.push_back(current);
		
	}
	//we push the path in the agent 
	addPath(myAgent, visited, myGrid);
	return count;
}

int DIJKSTRAFunction(Agent* myAgent, Grid* myGrid, Vector2D coinPosition)
{
	//Variables/////////////////////////////
	std::deque<node> frontier;
	std::vector<node> visited;
	node current;
	pairs neighBors[4];
	bool exists = false;
	bool existsToVisit = false;
	bool earlyExit = false;
	int count = 0;
	int indexToErase = -1;
	///////////////////////////

	//push first pos
	frontier.push_back(node{ (int)myGrid->pix2cell(myAgent->getPosition()).x,(int)myGrid->pix2cell(myAgent->getPosition()).y, pairs{-1,-1}, 0});
	
	while (!frontier.empty())
	{
		//actualize current node to search neighbors
		current = getLowestCostTill(frontier);;
		//Get neighbors
		findNeighbors(pairs{ current.NumColumn,current.NumRow }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY(), myGrid);
		//check neighbors
		for (int i = 0; i < 4; i++)
		{
			//Do the exit if it's node goal////////////////////////////
			if (((neighBors + i)->NumColumn == (int)coinPosition.x) && ((neighBors + i)->NumRow == (int)coinPosition.y))
			{				
				visited.push_back(current);
				visited.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs { current.NumColumn,current.NumRow } });
				earlyExit = true;
				break;
			}
			///////////////////////////////////////////////////////////

			//checking it exists/////////////////////////////////////////////////////////////////
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
							//Check if the cost is lower
							if ( (current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow }, pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid)) < t->costTill)
							{
								//change the existing with the new cost and camefrom
								t->costTill = (current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow }, pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid));
								t->came_from = pairs{current.NumColumn,current.NumRow};
							}
						}
					}
				}
				//if its not in any queue
				if ((!existsToVisit) && (!exists))
				{
					frontier.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs { current.NumColumn,current.NumRow },current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow }, pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid) });
				}
				//bools to false
				exists = false;
				existsToVisit = false;
			}
			/////////////////////////////////////////////////////////////////////////////////////
		}

		//if we found objective
		if (earlyExit)
		{
			break;
		}
		indexToErase = 0;
		//Get out node already searched
		for (auto t = frontier.begin(); t != frontier.end(); ++t)
		{
			if ((current.NumRow == t->NumRow) && (current.NumColumn == t->NumColumn))
			{
				break;
			}
			else
				indexToErase++;
		}
		frontier.erase(frontier.begin()+indexToErase);
		count++;
		//Push visited node
		visited.push_back(current);

	}

	//we push the path in the agent 
	addPath(myAgent, visited, myGrid);
	return count;
}

int ASTARFunction(Agent* myAgent,pairs myUbi, Grid* myGrid, Vector2D coinPosition)
{
	//Variables/////////////////////////////
	std::deque<node> frontier;
	std::vector<node> visited;
	node current;
	pairs neighBors[4];
	bool exists = false;
	bool existsToVisit = false;
	bool earlyExit = false;
	int count = 0;
	int indexToErase = -1;
	///////////////////////////

	//push first pos
	frontier.push_back(node{ myUbi.NumColumn,myUbi.NumRow, pairs{-1,-1}, myHeuristic(myUbi ,pairs{(int)coinPosition.x,(int)coinPosition.y}) });

	while (!frontier.empty())
	{
		//actualize current node to search neighbors
		current = getLowestCostTill(frontier);;
		//Get neighbors
		findNeighbors(pairs{ current.NumColumn,current.NumRow }, neighBors, myGrid->getNumCellX(), myGrid->getNumCellY(), myGrid);
		//check neighbors
		for (int i = 0; i < 4; i++)
		{
			//Do the exit if it's node goal////////////////////////////
			if (((neighBors + i)->NumColumn == (int)coinPosition.x) && ((neighBors + i)->NumRow == (int)coinPosition.y))
			{
				visited.push_back(current);
				visited.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,pairs { current.NumColumn,current.NumRow } });
				earlyExit = true;
				break;
			}
			///////////////////////////////////////////////////////////

			//checking it exists/////////////////////////////////////////////////////////////////
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
							//Check if the cost is lower
							if (((current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow }, pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid)) + myHeuristic(pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, pairs{(int)coinPosition.x,(int)coinPosition.y})) < t->costTill)
							{
								//change the existing with the new cost and camefrom
								t->costTill = ((current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow }, pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid)) + myHeuristic(pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, pairs{ (int)coinPosition.x,(int)coinPosition.y }));
								t->came_from = pairs{ current.NumColumn,current.NumRow };
							}
						}
					}
				}
				//if its not in any queue
				if ((!existsToVisit) && (!exists))
				{
					frontier.push_back(node{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow,
						pairs { current.NumColumn,current.NumRow },
						((current.costTill + getCostBetweenNodes(pairs{ current.NumColumn,current.NumRow },	pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, myGrid)) + myHeuristic(pairs{ (neighBors + i)->NumColumn,(neighBors + i)->NumRow }, pairs{ (int)coinPosition.x,(int)coinPosition.y })) });
				}
				//bools to false
				exists = false;
				existsToVisit = false;
			}
			/////////////////////////////////////////////////////////////////////////////////////
		}
		//if we found objective
		if (earlyExit)
		{
			break;
		}
		indexToErase = 0;
		//Get out node already searched
		for (auto t = frontier.begin(); t != frontier.end(); ++t)
		{
			if ((current.NumRow == t->NumRow) && (current.NumColumn == t->NumColumn))
			{
				break;
			}
			else
				indexToErase++;
		}
		frontier.erase(frontier.begin() + indexToErase);
		count++;
		//Push visited node
		visited.push_back(current);
	}
	//we push the path in the agent 
	addPath(myAgent, visited, myGrid);
	return count;
}

void findNeighbors(pairs ubication, pairs* neighborhood, int maxX, int maxY, Grid* myGrid)
{
	//Vecino izq
	if ((ubication.NumColumn -1 > 0) && (myGrid->terrain[ubication.NumRow][ubication.NumColumn - 1] ==1))
	{
		neighborhood[0] = pairs{ ubication.NumColumn - 1 ,ubication.NumRow};
	}
	else
	{
		neighborhood[0] = pairs{- 1 ,-1};
	}
	//vecino derech
	if ((ubication.NumColumn +1 < maxX) && (myGrid->terrain[ubication.NumRow][ubication.NumColumn + 1] == 1))
	{
		neighborhood[1] = pairs{ ubication.NumColumn + 1 , ubication.NumRow };
	}
	else
	{
		neighborhood[1] = pairs{ -1 ,-1 };
	}
	//vecino arriba
	if ((ubication.NumRow - 1 > 0) && (myGrid->terrain[ubication.NumRow-1][ubication.NumColumn] == 1))
	{
		neighborhood[2] = pairs{ ubication.NumColumn  , ubication.NumRow - 1 };
	}
	else
	{
		neighborhood[2] = pairs{ -1 ,-1 };
	}
	//vecino abajo
	if ((ubication.NumRow + 1 < maxY) && (myGrid->terrain[ubication.NumRow + 1][ubication.NumColumn] == 1))
	{
		neighborhood[3] = pairs{ ubication.NumColumn  , ubication.NumRow + 1 };
	}
	else
	{
		neighborhood[3] = pairs{ -1 ,-1 };
	}
}

void addPath(Agent* myAgent, std::vector<node> visitedNodes, Grid *myGrid)
{
	std::vector<node> finalPath;
	pairs toSearch{ visitedNodes.back().NumColumn,visitedNodes.back().NumRow };
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

int getCostBetweenNodes(pairs nodeA, pairs nodeB, Grid*myGrid)
{
	//Y y despues X
	int cost = (myGrid->terrain[nodeA.NumRow][nodeA.NumColumn] + myGrid->terrain[nodeB.NumRow][nodeB.NumColumn]) / 2;
	return cost;
}

node getLowestCostTill(std::deque<node> frontier)
{
	node lowest;
	lowest = frontier.front();
	for (auto t = frontier.begin(); t != frontier.end(); ++t)
	{
		if (lowest.costTill > t->costTill)
		{
			lowest = *t;
		}
	}

	return lowest;
}

int myHeuristic(pairs nodeA, pairs nodeB)
{
	int diferenceY = nodeA.NumRow - nodeB.NumRow;
	int diferenceX = nodeA.NumColumn - nodeB.NumColumn;
	if (diferenceX < 0)
		diferenceX = -diferenceX;
	if (diferenceY < 0)
		diferenceY = -diferenceY;
	return diferenceX + diferenceY;
}