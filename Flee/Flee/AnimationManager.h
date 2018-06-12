/*
*	Author: Omer Sari
*/
#ifndef AnimationManager_H
#define AnimationManager_H

#include "AnimationGroup.h"
#include "FleeList.h"

class AnimationManager
{
public:
	static void Initialize();
	static AnimationData*  CreateAnimationsOf(std::string id, Constants::VisualLayers layerIndex);
	static void Tick(int dt);

private:
	AnimationManager();
	~AnimationManager();

	void Free();
	void TickAnimations(int dt);
	AnimationGroup* CloneAnimationGroup(AnimationData* data, std::string id);
	bool Read();

	FleeList<AnimationGroup*> _activeAnimations;
	FleeList<AnimationGroup> _templates;
	static AnimationManager* _current;
};

#endif
