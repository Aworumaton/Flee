/*
*	Author: Omer Sari
*/
#ifndef PathFinder_H
#define PathFinder_H
#include <limits>
#include "NavigationGridMap.h"
#include "FleeList.h"
#include "GameEntity.h"
#include "Constants.h"

class PathFinder : public Behaviour
{
public:
	PathFinder(FleeTransform* sourceTransform, NavigationGridMap* navMap);

	void Tick(int dt);

	void SetTarget(FleeTransform* target);
	bool WillMove();
	FleeTransform LocalTarget;
private:
	struct PathNode
	{
	public:
		PathNode* ArrivedFromNode;

		int x; //const
		int y; //const

		double CostOfArrival;
		double EstimatedCostToDestination;
		double EstimatedTotalCost()
		{
			return CostOfArrival + EstimatedCostToDestination;
		};


		void Reset()
		{
			CostOfArrival = std::numeric_limits<double>::infinity();
			EstimatedCostToDestination = std::numeric_limits<double>::infinity();
			ArrivedFromNode = nullptr;
		}
	};
	NavigationGridMap * _navMap;
	FleeTransform _globalTarget;
	bool _isInDestination;
	bool _isLost;
	FleeTransform* _sourceTransform;

	PathNode** _path;
	PathNode** _queue;
	int _queueSize;

	bool GetShortestPath(PathNode* const sourceNode, SDL_Point* targetNodeIndeces);

	void SetEstimatedCostToDestination(PathNode* a);
	SDL_Point GetGlobalTargetPosition();

	void PushNode(PathNode* node);
	PathNode* RemoveCheapestNode();
};
#endif
