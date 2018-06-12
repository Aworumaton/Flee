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

	FleeTransform* GlobalTarget;
	FleeTransform* LocalTarget;
private:
	struct PathNode
	{
	public:
		PathNode* ArrivedFromNode;

		int x; //const
		int y; //const

		bool IsVisited = false;
		double CostOfArrival;
		double EstimatedCostToDestination;
		double EstimatedTotalCost()
		{
			return CostOfArrival + EstimatedCostToDestination;
		};


		void Reset()
		{
			IsVisited = false;
			CostOfArrival = std::numeric_limits<double>::infinity();
			EstimatedCostToDestination = std::numeric_limits<double>::infinity();
			ArrivedFromNode = nullptr;
		}
	};
	NavigationGridMap * _navMap;

	FleeTransform* _sourceTransform;
	FleeTransform* _targetTransform;

	PathNode** _path;
	PathNode** _queue;
	int _queueSize;

	bool GetShortestPath(PathNode* const sourceNode, SDL_Point* targetNodeIndeces);

	void UpdateAdjacentNodesOf(PathNode* sourceNode);

	void SetEstimatedCostToDestination(PathNode* a);
	SDL_Point GetGlobalTargetPosition();

	void PushNode(PathNode* node);
	PathNode* RemoveCheapestNode();

};


#endif
