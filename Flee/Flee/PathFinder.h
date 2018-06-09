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
	SDL_Point* _queue;
	int _queueSize;

	bool GetShortestPath();

	void UpdateNodesUsingPath(int x, int y);

	int GetRealCostSquaredBetween(int aIndexX, int aIndexY, int bIndexX, int bIndexY);
	int GetRealCostSquaredBetweenDestination(int indexX, int indexY);

	void PushNode(SDL_Point node);
	SDL_Point PopNode();
	SDL_Point GetCheapestOf(SDL_Point const nodeIndex1, SDL_Point const nodeIndex2);
	

	void TestPrintPath(int x, int y);
};


#endif
