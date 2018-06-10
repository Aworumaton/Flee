#include "PathFinder.h"

PathFinder::PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap)
{
	_navMap = navMap;
	_sourceTransform = sourceTransform;

	_targetTransform = new FleeTransform();
	_targetTransform->Width = Character::Size;
	_targetTransform->Height = Character::Size;

	_queue = new PathNode*[_navMap->GridSize()];

	_path = new PathNode*[_navMap->GridWidth()];
	for (int i = 0; i < _navMap->GridWidth(); i++)
	{
		_path[i] = new PathNode[_navMap->GridHeight()];
	}
	_queueSize = 0;
}


void PathFinder::Tick(int dt)
{

	LocalTarget = nullptr;
	if (GlobalTarget != nullptr)
	{
		SDL_Point sourceIndeces;
		SDL_Point targetIndeces;

		FleeTransform tmpTarget;
		tmpTarget.X = GetGlobalTargetPosition().x;
		tmpTarget.Y = GetGlobalTargetPosition().y;
		tmpTarget.Width = 1;
		tmpTarget.Height = 1;
		//
		//FleeTransform tmpSource;
		//tmpSource.X = _sourceTransform->X + Character::Size;
		//tmpSource.Y = _sourceTransform->Y + Character::Size;
		//tmpSource.Width = 1;
		//tmpSource.Height = 1;

		_navMap->GetNearestBlockOfPosition(_sourceTransform, sourceIndeces.x, sourceIndeces.y);
		_navMap->GetNearestBlockOfPosition(&tmpTarget, targetIndeces.x, targetIndeces.y);

		//sourceIndeces.x = _sourceTransform->X / Character::Size;
		//sourceIndeces.y = _sourceTransform->Y / Character::Size;
		//
		//targetIndeces.x = GetGlobalTargetPosition().x / Character::Size;
		//targetIndeces.y = GetGlobalTargetPosition().y / Character::Size;

		if (sourceIndeces.x == targetIndeces.x && sourceIndeces.y == targetIndeces.y)
		{
			LocalTarget = GlobalTarget;
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

					_targetTransform->X = _navMap->GetBlockAt(targetIndeces.x, targetIndeces.y)->X ;
					_targetTransform->Y = _navMap->GetBlockAt(targetIndeces.x, targetIndeces.y)->Y ;
					LocalTarget = _targetTransform;

				}
			}
		}
	}
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
			_path[i][j].x = i;
			_path[i][j].y = j;
			_navMap->GetBlockAt(i, j)->DebugAnimation->SetAnimation("Inactive");
		}
	}

	sourceNode->IsVisited = true;
	sourceNode->CostOfArrival = 0;
	SetEstimatedCostToDestination(sourceNode);
	PushNode(sourceNode);



	while (_queueSize > 0)
	{
		PathNode* curNode = RemoveCheapestNode();

		NavigationGridBlock* curGridBlock = _navMap->GetBlockAt(curNode->x, curNode->y);
		_targetTransform->X = curGridBlock->X;
		_targetTransform->Y = curGridBlock->Y;

		//if (targetNodeIndeces.x == targetIndexX && targetNodeIndeces.y == targetIndexY)
		if (Constants::CheckCollision(_targetTransform, GlobalTarget))
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
					double dDistance = _navMap->GetRealCostSquaredBetween(curGridBlock, comparedGridBlock);

					if (comparedNode->CostOfArrival > (dDistance + curNode->CostOfArrival))
					{
						comparedNode->CostOfArrival = dDistance + curNode->CostOfArrival;
						comparedNode->ArrivedFromNode = curNode;
						if (!comparedNode->IsVisited)
						{
							comparedNode->IsVisited = true;
							SetEstimatedCostToDestination(comparedNode);
							PushNode(comparedNode);
						}
						UpdateAdjacentNodesOf(comparedNode);
					}
				}
			}
		}
	}

	//for (int j = 0; j < _navMap->GridHeight(); j++)
	//{
	//	for (int i = 0; i < _navMap->GridWidth(); i++)
	//	{
	//		int val = (int)(_path[i][j].CostOfArrival / 1000);
	//		if (_path[i][j].CostOfArrival == std::numeric_limits<double>::infinity())
	//		{
	//			val = -1;
	//		}
	//		else if (val < 10)
	//		{
	//			printf(" ");
	//		}
	//		printf("%d ", val);
	//	}
	//	printf("\n");
	//}

	return false;
}


void PathFinder::UpdateAdjacentNodesOf(PathNode* sourceNode)
{
	NavigationGridBlock* sourceBlock = _navMap->GetBlockAt(sourceNode->x, sourceNode->y);
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if ((i == 0 && j == 0) ||
				sourceNode->x + i < 0 || sourceNode->x + i >= _navMap->GridWidth() ||
				sourceNode->y + j < 0 || sourceNode->y + j >= _navMap->GridHeight())
			{
				continue;
			}

			PathNode* comparedNode = &_path[sourceNode->x + i][sourceNode->y + j];

			if (comparedNode->IsVisited)
			{
				NavigationGridBlock* comparedBlock = _navMap->GetBlockAt(comparedNode->x, comparedNode->y);

				int dDistance = _navMap->GetRealCostSquaredBetween(sourceBlock, comparedBlock);

				if (comparedNode->CostOfArrival > dDistance + sourceNode->CostOfArrival)
				{
					comparedNode->CostOfArrival = dDistance + sourceNode->CostOfArrival;
					comparedNode->ArrivedFromNode = sourceNode;
					UpdateAdjacentNodesOf(comparedNode);
				}
			}
		}
	}
}


//implement fibonacci heap 
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

	a->EstimatedCostToDestination = (dX * dX) + (dY * dY);
}

SDL_Point PathFinder::GetGlobalTargetPosition()
{
	int dX = GlobalTarget->X + (GlobalTarget->Width / 2);
	int dY = GlobalTarget->Y + (GlobalTarget->Height / 2);
	return SDL_Point{ dX, dY };
}

