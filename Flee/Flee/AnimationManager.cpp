/*
*	Author: Omer Sari
*/
#include "AnimationManager.h"

void AnimationManager::Tick(int dt)
{
	_current->TickAnimations(dt);
}

void AnimationManager::TickAnimations(int dt)
{
	for (int i = 0; i < _activeAnimations.Size(); i++)
	{
		AnimationGroup* currentAnimation = _activeAnimations.ItemAt(i);
		AnimationGroup::AnimationSet* currentAnimationSet = currentAnimation->ActiveAnimationSet();
		if (currentAnimationSet != NULL)
		{
			AnimationGroup::KeyFrame* oldFrame = currentAnimationSet->Frames.ItemAt(currentAnimation->ActiveKeyFrameIndex);
			oldFrame->TextureData->IsHidden = true;
		}

		if (currentAnimation->GetAnimationData()->IsDirty)
		{
			currentAnimation->GetAnimationData()->IsDirty = false;
			currentAnimation->SetActiveAnimationSet(currentAnimation->GetAnimationData()->GetActiveAnimationId());
			currentAnimationSet = currentAnimation->ActiveAnimationSet();
		}

		if (!currentAnimation->GetAnimationData()->IsHidden)    
		{
			AnimationGroup::KeyFrame* targetFrame = currentAnimationSet->Frames.ItemAt(currentAnimation->ActiveKeyFrameIndex);

			int cumilativeAnimatedTime = 0;
			int targetTime = dt;
			while (cumilativeAnimatedTime < targetTime)
			{
				targetFrame = currentAnimationSet->Frames.ItemAt(currentAnimation->ActiveKeyFrameIndex);

				if (cumilativeAnimatedTime + targetFrame->TargetDuration - targetFrame->ElapsedDuration < targetTime)
				{
					cumilativeAnimatedTime += targetFrame->TargetDuration - targetFrame->ElapsedDuration;
					targetFrame->ElapsedDuration = 0;
					currentAnimation->ActiveKeyFrameIndex = (currentAnimation->ActiveKeyFrameIndex + 1) % currentAnimationSet->Frames.Size();
				}
				else
				{
					targetFrame->ElapsedDuration += targetTime - cumilativeAnimatedTime;
					cumilativeAnimatedTime = targetTime;

				}
			}

			targetFrame->TextureData->IsHidden = false;
		}
	}
}


void AnimationManager::Initialize()
{

	if (_current != nullptr)
	{
		_current->Free();
	}

	_current = new AnimationManager();
}


AnimationData*  AnimationManager::CreateAnimationsOf(std::string id, Constants::VisualLayers layerIndex)
{
	AnimationData* data = new AnimationData();
	AnimationGroup* target = _current->CloneAnimationGroup(data, id);
	target->Register(layerIndex);

	_current->_activeAnimations.Add(target);
	return data;
}

AnimationManager::AnimationManager()
{
	Read();
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::Free()
{
}


AnimationGroup* AnimationManager::CloneAnimationGroup(AnimationData* data, std::string id)
{
	for (int i = 0; i < _templates.Size(); i++)
	{
		if (_templates.ItemAt(i).Id() == id)
		{
			return _templates.ItemAt(i).Clone(data);
		}
	}

	return nullptr;
}

bool AnimationManager::Read()
{
	//Success flag
	bool success = true;

	std::ifstream file("Resources/animations.txt");

	if (!file.is_open())
	{
		printf("Unable to load sprite animations file!\n");
		success = false;
	}
	else
	{
		std::string id = "";
		while (file >> id)
		{
			int animationCount;
			file >> animationCount;
			AnimationGroup* targetGroup = new AnimationGroup(id, animationCount);

			for (int i = 0; i < animationCount; i++)
			{

				std::string aniamtionId = "";
				file >> aniamtionId;

				int frameCount;
				file >> frameCount;


				int isRepeating;
				file >> isRepeating;

				targetGroup->AddAnimation(aniamtionId, isRepeating == 1, frameCount);

				for (int j = 0; j < frameCount; j++)
				{
					std::string spriteId = "";
					file >> spriteId;

					int frameDuration;
					file >> frameDuration;

					targetGroup->AddKeyFrame(aniamtionId, spriteId, frameDuration);
				}
			}

			_templates.Add(*targetGroup);
		}

		//Close the file
		file.close();
	}
	return success;

}

AnimationManager* AnimationManager::_current;
