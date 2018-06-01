#include "AnimationGroup.h"

AnimationGroup::AnimationGroup() {	};

AnimationGroup::AnimationGroup(std::string id, int animationCount) : _animations(animationCount)
{
	_id = id;
};

AnimationGroup* AnimationGroup::Clone(AnimationData* animationData)
{
	AnimationGroup* newGroup = new AnimationGroup( this->_id, this->_animations.Size());
	newGroup->_animationData = animationData;

	for (int i = 0; i < _animations.Size(); i++)
	{
		AnimationSet* clonedSet = _animations.ItemAt(i);
		AnimationSet* newSet = newGroup->AddAnimation(clonedSet->Id, clonedSet->IsRepeating, clonedSet->Frames.Size());

		//Animation* clone = new Animation(this->_id, this->_isRepeating, this->_frames.Size(), transform);
		for (int j = 0; j < clonedSet->Frames.Size(); j++)
		{
			KeyFrame* clonedFrame = clonedSet->Frames.ItemAt(j);
			SpriteData* newSpriteData = new SpriteData(clonedFrame->TextureData->Id());
			newSpriteData->IsHidden = true;
			newSpriteData->Transform = animationData->Transform;
			KeyFrame* newFrame = new KeyFrame{ newSpriteData , clonedFrame->TargetDuration, 0 };
			newSet->Frames.Add(newFrame);
		}
	}

	return newGroup;
};

void AnimationGroup::Register(Constants::VisualLayers layerIndex)
{
	for (int i = 0; i < _animations.Size(); i++)
	{
		AnimationSet* animationSet = _animations.ItemAt(i);

		for (int j = 0; j < animationSet->Frames.Size(); j++)
		{
			SpriteData* frameVisual = animationSet->Frames.ItemAt(j)->TextureData;
			FleeRenderer::Register(frameVisual, layerIndex);
		}
	}
};

AnimationGroup::AnimationSet* AnimationGroup::AddAnimation(std::string id, bool isRepeating, int frameCount)
{
	AnimationSet* animation = new AnimationSet(id, isRepeating, frameCount);
	_animations.Add(animation);
	return animation;
}

bool AnimationGroup::AddKeyFrame(std::string animationSetId, std::string spriteId, int duration)
{
	for (int i = 0; i < _animations.Size(); i++)
	{
		AnimationSet* target = _animations.ItemAt(i);
		if (target->Id == animationSetId)
		{
			SpriteData* newSpriteData = new SpriteData(spriteId);
			newSpriteData->IsHidden = true;
			KeyFrame* newFrame = new KeyFrame{ newSpriteData , duration };
			target->Frames.Add(newFrame);
			return true;
		}
	}
	return false;
};

std::string AnimationGroup::Id()
{
	return _id;
}

AnimationData* AnimationGroup::GetAnimationData()
{
	return _animationData;
}

AnimationGroup::AnimationSet* AnimationGroup::ActiveAnimationSet()
{
	return _activeAnimationSet;
}

void AnimationGroup::SetActiveAnimationSet(std::string id)
{
	for (int i = 0; i < _animations.Size(); i++)
	{
		AnimationSet* target = _animations.ItemAt(i);
		if (target->Id == id)
		{
			_activeAnimationSet = target;
			ActiveKeyFrameIndex = 0;
			return;
		}
	}
}