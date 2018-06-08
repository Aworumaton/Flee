#include "PathFinder.h"

PathFinder::PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap)
{
	_navMap = navMap;
	_sourceTransform = sourceTransform;

	_targetTransform = new FleeTransform();
	_targetTransform->Width = Character::Size;
	_targetTransform->Height = Character::Size;

	_path = new NavigationGridBlock*[_navMap->GridSize()];
	_queue = new NavigationGridBlock*[_navMap->GridSize()];

	_visitedNodes = new bool*[_navMap->GridWidth()];
	for (int i = 0; i < _navMap->GridWidth(); i++)
	{
		_visitedNodes[i] = new bool[_navMap->GridHeight()];
	}
	_queueSize = 0;
	_pathSize = 0;
}


void PathFinder::Tick(int dt)
{
	_queueSize = 0;
	_pathSize = 0;

	if (GlobalTarget != nullptr)
	{

		for (int i = 0; i < _navMap->GridWidth(); i++)
		{
			for (int j = 0; j < _navMap->GridWidth(); j++)
			{
				_visitedNodes[i][j] = false;
			}
		}


		PushNode(_navMap->GetBlockAt(_sourceTransform->X / Character::Size, _sourceTransform->Y / Character::Size));
		if(!GetShortestPath())
		{

		}

		if (_pathSize > 0)
		{
			printf("SOURCE X:%d Y:%d\n", _sourceTransform->X, _sourceTransform->Y);
			printf("Target X:%d Y:%d\n\n", GlobalTarget->X, GlobalTarget->Y);

			for (int i = _pathSize - 1; i >= 0; i--)
			{
				printf("path %d, %d\n", _path[i]->X, _path[i]->Y);
			}
			_targetTransform->X = _path[_pathSize - 1]->X;
			_targetTransform->Y = _path[_pathSize - 1]->Y;
			LocalTarget = _targetTransform;
		}

	}
	else
	{
		LocalTarget = nullptr;
	}
}

bool PathFinder::GetShortestPath()
{
	NavigationGridBlock* targetNode = PopNode();
	if (targetNode == nullptr)
	{
		return false;
	}
	_targetTransform->X = targetNode->X;
	_targetTransform->Y = targetNode->Y;

	if(Constants::CheckCollision(_targetTransform, GlobalTarget))
	{
		_path[_pathSize] = targetNode;
		_pathSize++;
		return true;
	}

	int curXIndex = targetNode->X / Character::Size;
	int curYIndex = targetNode->Y / Character::Size;

	_visitedNodes[curXIndex][curYIndex] = true;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			NavigationGridBlock* curNode = _navMap->GetBlockAt(curXIndex + i, curYIndex + j);
			if (curNode != nullptr && !curNode->IsBlocked && !_visitedNodes[curXIndex+i][curYIndex+j])
			{
				PushNode(curNode);
			}
		}
	}
	
	while (_queueSize > 0)
	{
		if (GetShortestPath())
		{
			_path[_pathSize] = targetNode;
			_pathSize++;
			return true;
		}
	}
	return false;
}



void PathFinder::PushNode(NavigationGridBlock* node)
{
	_queue[_queueSize] = node;
	int nodeIndex = _queueSize;
	_queueSize++;

	int targetNodeIndex = (nodeIndex-1) / 2;
	NavigationGridBlock* targetNode = _queue[targetNodeIndex];

	while (nodeIndex > 0)
	{
		if (GetClosestOf(node, targetNode) != targetNode)
		{
			return;
		}

		NavigationGridBlock* tmp = _queue[targetNodeIndex];
		_queue[targetNodeIndex] = _queue[nodeIndex];
		_queue[nodeIndex] = tmp;

		nodeIndex = targetNodeIndex;
		targetNodeIndex = (targetNodeIndex-1) / 2;
	}
}

NavigationGridBlock* PathFinder::PopNode()
{
	NavigationGridBlock* item;
	if (_queueSize > 0)
	{
		item = _queue[0];
		_queueSize--;
		_queue[0] = _queue[_queueSize];
	}
	else
	{
		return nullptr;
	}

	int nodeIndex = 0;

	int targetNodeIndex1 = nodeIndex*2+1;
	int targetNodeIndex2 = nodeIndex * 2 + 2;

	NavigationGridBlock* targetNode = nullptr;

	while (targetNodeIndex1 < _queueSize)
	{
		if (targetNodeIndex2 < _queueSize)
		{
			targetNode = GetClosestOf(_queue[targetNodeIndex1], _queue[targetNodeIndex2]);
		}
		else
		{
			targetNode = _queue[targetNodeIndex1];
		}

		targetNode = GetClosestOf(_queue[nodeIndex], targetNode);

		if (targetNode == _queue[nodeIndex])
		{
			break;
		}

		_queue[nodeIndex] = targetNode;

		if (targetNode == _queue[targetNodeIndex1])
		{
			nodeIndex = targetNodeIndex1;
		}
		else
		{
			nodeIndex = targetNodeIndex2;
		}
		targetNodeIndex1 = nodeIndex * 2 + 1;
		targetNodeIndex2 = targetNodeIndex1 + 1;
	}

	return item;
}

NavigationGridBlock* const PathFinder::GetClosestOf(NavigationGridBlock* const node1, NavigationGridBlock* const node2)
{
	int xDistance = GlobalTarget->X - node1->X;
	int yDistance = GlobalTarget->Y - node1->Y;
	double node1Distance = xDistance * xDistance + yDistance * yDistance;

	xDistance = GlobalTarget->X - node2->X;
	yDistance = GlobalTarget->Y - node2->Y;
	double node2Distance = xDistance * xDistance + yDistance * yDistance;

	if (node1Distance < node2Distance)
	{
		return node1;
	}
	return node2;
}

