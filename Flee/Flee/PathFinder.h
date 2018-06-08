#ifndef PathFinder_H
#define PathFinder_H
#include "NavigationGridMap.h"
#include "FleeList.h"
#include "GameEntity.h"
#include "Constants.h"

class PathFinder : public Behaviour
{
public:
	PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap);

	void Tick(int dt);

	FleeTransform* GlobalTarget;
	FleeTransform* LocalTarget;
private:
	NavigationGridMap * _navMap;
	FleeTransform* _sourceTransform;
	FleeTransform* _targetTransform;
	NavigationGridBlock** _path;
	NavigationGridBlock** _queue;
	bool** _visitedNodes;
	int _queueSize;
	int _pathSize;


	bool GetShortestPath();



	void PushNode(NavigationGridBlock* node);
	NavigationGridBlock* PopNode();
	NavigationGridBlock* const GetClosestOf(NavigationGridBlock* const node1, NavigationGridBlock* const node2);
};


#endif
