#ifndef AnimationGroup_H
#define AnimationGroup_H
#include <string>
#include "FleeList.h"
#include "FleeLibrary.h"
#include "Constants.h"
#include "FleeRenderer.h"


class AnimationGroup
{
public:

	struct KeyFrame
	{
		SpriteData* TextureData;
		int TargetDuration;
		int ElapsedDuration;
	};

	struct AnimationSet
	{
		AnimationSet(std::string id, bool isRepeating, int frameCount) : Frames(frameCount)
		{
			Id = id;
			IsRepeating = isRepeating;
		};

		FleeList<KeyFrame*> Frames;
		bool IsRepeating;
		std::string Id;
	};


	AnimationGroup();
	AnimationGroup(std::string id, int animationCount);

	AnimationGroup* Clone(AnimationData* animationData);	
	void Register(Constants::VisualLayers layerIndex);

	AnimationSet* AddAnimation(std::string id, bool isRepeating, int frameCount);
	bool AddKeyFrame(std::string animationSetId, std::string spriteId, int duration);

	std::string Id();
	AnimationData * GetAnimationData();
	AnimationSet* ActiveAnimationSet();
	void SetActiveAnimationSet(std::string id);

	int ActiveKeyFrameIndex;
private:
	std::string _id;
	FleeList<AnimationSet*> _animations;
	AnimationData * _animationData;
	AnimationSet* _activeAnimationSet;
};
#endif
