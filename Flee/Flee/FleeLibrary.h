#ifndef FleeLibrary_H
#define FleeLibrary_H
#include <string>
#include "FleeList.h"
#include "FleeList.h"

class FleeTransform
{
public:
	int X = 0;
	int Y = 0;

	int Width = 0;
	int Height = 0;

	int Rotation = 0;
};




class AnimationData
{
private:

public:
	AnimationData()
	{
		Transform = new FleeTransform();
		Transform->Width = -1;
		Transform->Height = -1;
	}

	void SetAnimation(std::string id)
	{
		_activeAnimation = id;
		IsDirty = true;
	};

	std::string GetActiveAnimationId()
	{
		return _activeAnimation;
	};

	std::string GetOneShotAnimation()
	{
		return _oneShotAnimation;
	};

	FleeTransform * Transform;
	bool IsDirty;
	bool IsHidden;
	int ElapsedTime;
private:
	std::string _activeAnimation;
	std::string _oneShotAnimation;
};

class SpriteData
{
public:
	SpriteData(std::string id)
	{
		_id = id;
		IsHidden = false;
		Transform = new FleeTransform();
		Transform->Width = -1;
		Transform->Height = -1;
	};

	~SpriteData()
	{
		delete(Transform);
	}

	bool InitializeWith(unsigned int flags, int suggestedWith, int suggestedHeight)
	{
		_isWall = (flags & FlagTypes::Wall) == FlagTypes::Wall;

		if (Transform->Width < 0)
		{
			Transform->Width = suggestedWith;
		}

		if (Transform->Height < 0)
		{
			Transform->Height = suggestedHeight;
		}


		return true;
	};
	
	bool IsWall()
	{
		return _isWall;
	};

	std::string Id()
	{
		return _id;
	};

	FleeTransform* Transform; //World transform
	bool IsHidden;

private:
	std::string _id;
	bool _isWall;

	enum FlagTypes
	{
		None = 0b0000000000000000,
		Ground = 0b0000000000000001,
		Wall = 0b0000000000000010,
		Door = 0b0000000000000100,
		Hiding_Place = 0b0000000000001000,
	};

};


#endif