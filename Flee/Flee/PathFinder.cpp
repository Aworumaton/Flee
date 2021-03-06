/*
*	Author: Omer Sari
*/
#include "PathFinder.h"

PathFinder::PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap)
{
	_navMap = navMap;
	_sourceTransform = sourceTransform;

	_queue = new PathNode*[_navMap->GridWidth()*_navMap->GridHeight()];

	_path = new PathNode*[_navMap->GridWidth()];
	for (int i = 0; i < _navMap->GridWidth(); i++)
	{
		_path[i] = new PathNode[_navMap->GridHeight()];
		for (int j = 0; j < _navMap->GridHeight(); j++)
		{
			_path[i][j].x = i;
			_path[i][j].y = j;
		}
	}
	_queueSize = 0;

	SetTarget(sourceTransform);
}


void PathFinder::Tick(int dt)
{
	if (Constants::CheckCollision(_sourceTransform, &_globalTarget))
	{
		_isInDestination = true;
		return;
	}
	
	_isInDestination = false;
	_isLost = false;

	SDL_Point sourceIndeces;
	SDL_Point targetIndeces;
		
	_navMap->GetNearestValidBlockAtPosition(_sourceTransform, sourceIndeces.x, sourceIndeces.y);
	_navMap->GetNearestValidBlockAtPosition(&_globalTarget, targetIndeces.x, targetIndeces.y);

	if (sourceIndeces.x == targetIndeces.x && sourceIndeces.y == targetIndeces.y)
	{
		LocalTarget.X = _globalTarget.X;
		LocalTarget.Y = _globalTarget.Y;
	}
	else
	{
		PathNode* sourceNode = &_path[sourceIndeces.x][sourceIndeces.y];
		if (GetShortestPath(sourceNode, &targetIndeces))
		{

			PathNode* arrivedNode = _path[targetIndeces.x][targetIndeces.y].ArrivedFromNode;
			if (arrivedNode != nullptr)
			{

				while (sourceIndeces.x != arrivedNode->x || sourceIndeces.y != arrivedNode->y)
				{
					_navMap->GetBlockAt(arrivedNode->x, arrivedNode->y)->DebugAnimation->SetAnimation("Active");

					targetIndeces.x = arrivedNode->x;
					targetIndeces.y = arrivedNode->y;

					arrivedNode = arrivedNode->ArrivedFromNode;
				}

				LocalTarget.X = _navMap->GetBlockAt(targetIndeces.x, targetIndeces.y)->X;
				LocalTarget.Y = _navMap->GetBlockAt(targetIndeces.x, targetIndeces.y)->Y;
			}
		}
		else
		{

			_isLost = true;
		}
	}
}

void PathFinder::SetTarget(FleeTransform * target)
{
	_globalTarget.Height = target->Height;
	_globalTarget.Width = target->Width;
	_globalTarget.X = target->X;
	_globalTarget.Y = target->Y;
	_globalTarget.Rotation = target->Rotation;
}

bool PathFinder::WillMove()
{
	return !_isInDestination && !_isLost;
}

//using A*
bool PathFinder::GetShortestPath(PathNode* const sourceNode, SDL_Point* targetNodeIndeces)
{
	_queueSize = 0;

	for (int i = 0; i < _navMap->GridWidth(); i++)
	{
		for (int j = 0; j < _navMap->GridHeight(); j++)
		{
			_path[i][j].Reset();
			if (_navMap->GetBlockAt(i, j)->IsBlocked)
			{
				_navMap->GetBlockAt(i, j)->DebugAnimation->SetAnimation("Disabled");
			}
			else
			{
				_navMap->GetBlockAt(i, j)->DebugAnimation->SetAnimation("Inactive");
			}
		}
	}

	sourceNode->CostOfArrival = 0;
	SetEstimatedCostToDestination(sourceNode);
	PushNode(sourceNode);

	int globalTargetX;
	int globalTargetY;
	_navMap->GetNearestValidBlockAtPosition(&_globalTarget, globalTargetX, globalTargetY);


	while (_queueSize > 0)
	{
		PathNode* curNode = RemoveCheapestNode();

		NavigationGridBlock* curGridBlock = _navMap->GetBlockAt(curNode->x, curNode->y);
		//_targetTransform->X = curGridBlock->X;
		//_targetTransform->Y = curGridBlock->Y;

		//if (Constants::CheckCollision(_targetTransform, GlobalTarget))
		if (curNode->x == globalTargetX && curNode->y == globalTargetY)
		{
			targetNodeIndeces->x = curNode->x;
			targetNodeIndeces->y = curNode->y;
			return true;
		}

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if ((i == 0 && j == 0) ||
					curNode->x + i < 0 || curNode->x + i >= _navMap->GridWidth() ||
					curNode->y + j < 0 || curNode->y + j >= _navMap->GridHeight())
				{
					continue;
				}

				PathNode* comparedNode = &_path[curNode->x + i][curNode->y + j];

				NavigationGridBlock* comparedGridBlock = _navMap->GetBlockAt(comparedNode->x, comparedNode->y);

				if (comparedGridBlock != nullptr && !comparedGridBlock->IsBlocked)
				{
					double dDistance = _navMap->GetRealCostBetween(curGridBlock, comparedGridBlock);

					if (comparedNode->CostOfArrival > (dDistance + curNode->CostOfArrival))
					{
						comparedNode->CostOfArrival = dDistance + curNode->CostOfArrival;
						comparedNode->ArrivedFromNode = curNode;

						SetEstimatedCostToDestination(comparedNode);
						PushNode(comparedNode);
					}
				}
			}
		}
	}
	return false;
}

//implement fibonacci heap later
void PathFinder::PushNode(PathNode* node)
{
	_queue[_queueSize] = node;
	_queueSize++;
}

PathFinder::PathNode* PathFinder::RemoveCheapestNode()
{
	int cheapestIndex = 0;
	for (int i = 1; i < _queueSize; i++)
	{
		if (_queue[i]->EstimatedTotalCost() < _queue[cheapestIndex]->EstimatedTotalCost())
		{
			cheapestIndex = i;
		}
	}

	PathNode* result = _queue[cheapestIndex];

	_queueSize--;
	_queue[cheapestIndex] = _queue[_queueSize];

	return result;
}


//Euclidian Distance
void PathFinder::SetEstimatedCostToDestination(PathNode* a)
{
	NavigationGridBlock* aNode = _navMap->GetBlockAt(a->x, a->y);
	SDL_Point tPos = GetGlobalTargetPosition();

	int dX = aNode->X - tPos.x;
	int dY = aNode->Y - tPos.y;

	a->EstimatedCostToDestination = sqrt((dX * dX) + (dY * dY));
}

SDL_Point PathFinder::GetGlobalTargetPosition()
{
	int dX = _globalTarget.X + (_globalTarget.Width / 2);
	int dY = _globalTarget.Y + (_globalTarget.Height / 2);
	return SDL_Point{ dX, dY };
}

