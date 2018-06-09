#include "PathFinder.h"

PathFinder::PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap)
{
	_navMap = navMap;
	_sourceTransform = sourceTransform;

	_targetTransform = new FleeTransform();
	_targetTransform->Width = Character::Size;
	_targetTransform->Height = Character::Size;

	_queue = new SDL_Point[_navMap->GridSize()];

	_path = new PathNode*[_navMap->GridWidth()];
	for (int i = 0; i < _navMap->GridWidth(); i++)
	{
		_path[i] = new PathNode[_navMap->GridHeight()];
	}
	_queueSize = 0;
}


void PathFinder::Tick(int dt)
{

	if (GlobalTarget != nullptr)
	{
		GetShortestPath();


		{
			printf("SOURCE X:%d Y:%d\n", _sourceTransform->X, _sourceTransform->Y);
			printf("Target X:%d Y:%d\n\n", GlobalTarget->X, GlobalTarget->Y);


			int testIndexX = GlobalTarget->X / Character::Size;
			int testIndexY = GlobalTarget->Y / Character::Size;
			TestPrintPath(testIndexX, testIndexY);


			int sourceIndexX = _sourceTransform->X / Character::Size;
			int sourceIndexY = _sourceTransform->Y / Character::Size;


			int targetIndexX = testIndexX;
			int targetIndexY = testIndexY;
			PathNode* arrivedNode = _path[targetIndexX][targetIndexY].ArrivedFromNode;
			if (arrivedNode != nullptr)
			{

				while (sourceIndexX != arrivedNode->x || sourceIndexY != arrivedNode->y)
				{
					_navMap->GetBlockAt(arrivedNode->x, arrivedNode->y)->DebugAnimation->SetAnimation("Active");

					targetIndexX = arrivedNode->x;
					targetIndexY = arrivedNode->y;

					arrivedNode = arrivedNode->ArrivedFromNode;
				}



				_targetTransform->X = _navMap->GetBlockAt(targetIndexX, targetIndexY)->X;
				_targetTransform->Y = _navMap->GetBlockAt(targetIndexX, targetIndexY)->Y;
				LocalTarget = _targetTransform;

			}
			else
			{
				LocalTarget = nullptr;
			}
		}

	}
	else
	{
		LocalTarget = nullptr;
	}
}

void PathFinder::TestPrintPath(int x, int y)
{

	//int sourceIndexX = _sourceTransform->X / Character::Size;
	//int sourceIndexY = _sourceTransform->Y / Character::Size;
	//
	//
	//if (sourceIndexX != x || sourceIndexY != y)
	//{
	//	int targetIndexX = _path[x][y].ArrivedFromNode->x;
	//	int targetIndexY = _path[x][y].ArrivedFromNode->y;
	//	TestPrintPath(targetIndexX, targetIndexY);
	//}
	//
	//printf("path %d, %d\n", x, y);
}

//using A*
bool PathFinder::GetShortestPath()
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

 	int sourceIndexX = _sourceTransform->X / Character::Size;
	int sourceIndexY = _sourceTransform->Y / Character::Size;

	int targetIndexX = GlobalTarget->X / Character::Size;
	int targetIndexY = GlobalTarget->Y / Character::Size;

	_path[sourceIndexX][sourceIndexY].IsVisited = true;
	_path[sourceIndexX][sourceIndexY].CostOfArrival = 0;
	_path[sourceIndexX][sourceIndexY].EstimatedCostToDestination = GetRealCostSquaredBetweenDestination(sourceIndexX, sourceIndexY);
	PushNode(SDL_Point{ sourceIndexX, sourceIndexY });



	while (_queueSize > 0)
	{
		SDL_Point targetNodeIndeces = PopNode();

		_targetTransform->X = _navMap->GetBlockAt(targetNodeIndeces.x, targetNodeIndeces.y)->X;
		_targetTransform->Y = _navMap->GetBlockAt(targetNodeIndeces.x, targetNodeIndeces.y)->Y;

		//if (Constants::CheckCollision(_targetTransform, GlobalTarget))
		if (targetNodeIndeces.x == targetIndexX && targetNodeIndeces.y == targetIndexY)
		{
			return true;
		}

		int curXIndex = targetNodeIndeces.x;
		int curYIndex = targetNodeIndeces.y;

		PathNode* targetNode = &_path[curXIndex][curYIndex];
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0)
				{
					continue;
				}

				NavigationGridBlock* curGridBlock = _navMap->GetBlockAt(curXIndex + i, curYIndex + j);
				if (curGridBlock != nullptr && !curGridBlock->IsBlocked)
				{
					PathNode* curNode = &_path[curXIndex + i][curYIndex + j];
					double dDistance = GetRealCostSquaredBetween(curXIndex + i, curYIndex + j, curXIndex, curYIndex);
					if (_path[curXIndex + i][curYIndex + j].CostOfArrival > (dDistance + targetNode->CostOfArrival)) //handle diogonal movement
					{
						curNode->CostOfArrival = dDistance + _path[curXIndex][curYIndex].CostOfArrival;
						curNode->ArrivedFromNode = &_path[curXIndex][curYIndex];
						if (!curNode->IsVisited)
						{
							curNode->IsVisited = true;
							curNode->EstimatedCostToDestination = GetRealCostSquaredBetweenDestination(curXIndex + i, curYIndex + j);
							PushNode(SDL_Point{ curXIndex + i , curYIndex + j });
						}
					//	else
						{
							UpdateNodesUsingPath(curXIndex + i, curYIndex + j);


							SDL_Point tmpNode;
							for (int i = 0; i < _queueSize; i++)
							{
								int nodeIndex = i;

								int targetNodeIndex1 = nodeIndex * 2 + 1;
								int targetNodeIndex2 = nodeIndex * 2 + 2;
								while (targetNodeIndex1 < _queueSize)
								{
									if (targetNodeIndex2 < _queueSize)
									{
										tmpNode = GetCheapestOf(_queue[targetNodeIndex1], _queue[targetNodeIndex2]);
									}
									else
									{
										tmpNode = _queue[targetNodeIndex1];
									}

									tmpNode = GetCheapestOf(_queue[nodeIndex], tmpNode);

									if (tmpNode.x == _queue[nodeIndex].x && tmpNode.y == _queue[nodeIndex].y)
									{
										break;
									}

									SDL_Point tmpSwapNode = _queue[nodeIndex];
									_queue[nodeIndex] = tmpNode;


									if (tmpNode.x == _queue[targetNodeIndex1].x && tmpNode.y == _queue[targetNodeIndex1].y)
									{
										nodeIndex = targetNodeIndex1;
									}
									else
									{
										nodeIndex = targetNodeIndex2;
									}


									_queue[nodeIndex] = tmpSwapNode;

									targetNodeIndex1 = nodeIndex * 2 + 1;
									targetNodeIndex2 = targetNodeIndex1 + 1;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}


void PathFinder::UpdateNodesUsingPath(int x, int y)
{
	PathNode* sourceNode = &_path[x][y];
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}

			PathNode* curNode = &_path[x + i][y + j];

			if (curNode->IsVisited)
			{
				double dDistance = GetRealCostSquaredBetween(x + i, y + j, x, y);

				if (curNode->CostOfArrival > dDistance + sourceNode->CostOfArrival)
				{
					curNode->CostOfArrival = dDistance + sourceNode->CostOfArrival;
					curNode->ArrivedFromNode = sourceNode;

					//printf("curNode->CostOfArrival %f   -%f\n", curNode->CostOfArrival, dDistance);

					UpdateNodesUsingPath(i + x, j + y);

				}
			}
		}
	}
}


void PathFinder::PushNode(SDL_Point node)
{
	_queue[_queueSize] = node;
	int nodeIndex = _queueSize;
	_queueSize++;

	int targetNodeIndex = (nodeIndex - 1) / 2;
	SDL_Point targetNode = _queue[targetNodeIndex];

	while (nodeIndex > 0)
	{
		SDL_Point result = GetCheapestOf(node, targetNode);
		if (result.x == node.x && result.y == node.y)
		{
			return;
		}

		SDL_Point tmp = _queue[targetNodeIndex];
		_queue[targetNodeIndex] = _queue[nodeIndex];
		_queue[nodeIndex] = tmp;

		nodeIndex = targetNodeIndex;
		targetNodeIndex = (targetNodeIndex - 1) / 2;
	}
}

SDL_Point PathFinder::PopNode()
{
	SDL_Point item;
	if (_queueSize > 0)
	{
		item = _queue[0];
		_queueSize--;
		_queue[0] = _queue[_queueSize];
	}
	else
	{
		return SDL_Point();
	}

	int nodeIndex = 0;

	int targetNodeIndex1 = nodeIndex * 2 + 1;
	int targetNodeIndex2 = nodeIndex * 2 + 2;

	SDL_Point targetNode;

	while (targetNodeIndex1 < _queueSize)
	{
		if (targetNodeIndex2 < _queueSize)
		{
			targetNode = GetCheapestOf(_queue[targetNodeIndex1], _queue[targetNodeIndex2]);
		}
		else
		{
			targetNode = _queue[targetNodeIndex1];
		}

		targetNode = GetCheapestOf(_queue[nodeIndex], targetNode);

		if (targetNode.x == _queue[nodeIndex].x && targetNode.y == _queue[nodeIndex].y)
		{
			break;
		}

		SDL_Point tmpSwapNode = _queue[nodeIndex];
		_queue[nodeIndex] = targetNode;


		if (targetNode.x == _queue[targetNodeIndex1].x && targetNode.y == _queue[targetNodeIndex1].y)
		{
			nodeIndex = targetNodeIndex1;
		}
		else
		{
			nodeIndex = targetNodeIndex2;
		}


		_queue[nodeIndex] = tmpSwapNode;

		targetNodeIndex1 = nodeIndex * 2 + 1;
		targetNodeIndex2 = targetNodeIndex1 + 1;
	}

	return item;
}


//Euclidian Distance
int PathFinder::GetRealCostSquaredBetween(int aIndexX, int aIndexY, int bIndexX, int bIndexY)
{
	NavigationGridBlock* aNode = _navMap->GetBlockAt(aIndexX, aIndexY);
	NavigationGridBlock* bNode = _navMap->GetBlockAt(bIndexX, bIndexY);

	int dX = aNode->X - bNode->X;
	int dY = aNode->Y - bNode->Y;

	return (dX * dX) + (dY * dY);
}

//Euclidian Distance
int PathFinder::GetRealCostSquaredBetweenDestination(int indexX, int indexY)
{
	NavigationGridBlock* aNode = _navMap->GetBlockAt(indexX, indexY);

	int dX = aNode->X - GlobalTarget->X;
	int dY = aNode->Y - GlobalTarget->Y;

	return (dX * dX) + (dY * dY);
}

SDL_Point PathFinder::GetCheapestOf(SDL_Point const nodeIndex1, SDL_Point const nodeIndex2)
{
	PathNode* node1 = &_path[nodeIndex1.x][nodeIndex1.y];
	PathNode* node2 = &_path[nodeIndex2.x][nodeIndex2.y];
	if (node1->CostOfArrival + node1->EstimatedCostToDestination < node2->CostOfArrival + node2->EstimatedCostToDestination)
	{
		return nodeIndex1;
	}
	return nodeIndex2;
}

