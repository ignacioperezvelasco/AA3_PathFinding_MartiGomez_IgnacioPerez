#pragma once
#include "Agent.h"
#include "Vector2D.h"

class PathFollowing :
	public Agent::SteeringBehavior
{
public:
	enum pathFindingType { BFS, DIJKSTRA, GBFS, ASTAR, NONE };
	PathFollowing();
	~PathFollowing();
	void applySteeringForce(Agent *agent, float dtime);
};
