#ifndef GameEntity_H
#define GameEntity_H
#include "FleeLibrary.h"
#include "FleeList.h"


class Behaviour
{
public:
	Behaviour() {};
	std::string  Id;
};

class GameEntity
{
public :
	virtual ~GameEntity()
	{

	};

	virtual void Tick(int dt) = 0;

	FleeTransform* Transform;

protected:
	FleeList<Behaviour*> _behaviours;
};


class Character : public GameEntity
{
public:
	virtual ~Character()
	{
		GameEntity::~GameEntity();
	};

	virtual void Tick(int dt)
	{

	};

	std::string  Id;

protected:
	AnimationData* _visualData;
};

#endif

