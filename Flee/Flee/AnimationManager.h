#ifndef AnimationManager_H
#define AnimationManager_H
#include "FleeRenderer.h"
#include "FleeList.h"
#include "FleeRenderer.h"


class Animation //coupled with animationset 
{
public:
	struct KeyFrame
	{
		SpriteData* TextureData;
		int Duration;
	};

	Animation()	{	};

	Animation(std::string id, bool isRepeating, int frameCount, FleeTransform* transform) : _frames(frameCount)
	{
		_id = id;
		_transform = transform;
	};

	void AddKeyFrame(std::string id, int duration)
	{
		SpriteData* frameVisual = new SpriteData(id);
		FleeRenderer::Register(frameVisual, 1);

		_transform->Width = frameVisual->Transform->Width;
		_transform->Height = frameVisual->Transform->Height;
		frameVisual->Transform = _transform;

		_frames.Add(new KeyFrame{ frameVisual , duration });
	};

	void Free()
	{
		for (int i = _frames.Size() - 1; i >= 0; i--)
		{
			KeyFrame* item = _frames.ItemAt(i);
			_frames.RemoveAt(i);
			delete(item);
		}
	};

	Animation* Clone(FleeTransform* transform)
	{
		Animation* clone = new Animation(this->_id, this->_isRepeating, this->_frames.Size(), transform);
		for (int i = 0; i < this->_frames.Size(); i++)
		{
			KeyFrame* frame = _frames.ItemAt(i);
			clone->AddKeyFrame(frame->TextureData->Id(), frame->Duration);
		}

		return clone;
	};

	std::string Id()
	{
		return _id;
	};

private:

	FleeList<KeyFrame*> _frames;
	bool _isRepeating;
	std::string _id;
	FleeTransform* _transform;
};

class AnimationSet
{
public:
	AnimationSet() {	};

	AnimationSet(std::string id, int animationCount) : _animations(animationCount)
	{
		_id = id;
	};

	bool SetAnimation(std::string id)
	{
		for (int i = 0; i < _animations.Size(); i++)
		{
			if (_animations.ItemAt(i)->Id() == id)
			{
				_activeAnimation = _animations.ItemAt(i);
				return true;
			}
		}

		return false;
	};

	AnimationSet* Clone()
	{
		AnimationSet* clone = new AnimationSet(this->_id, this->_animations.Size());
		clone->_activeAnimation = this->_activeAnimation;
		clone->Transform.Width = this->Transform.Width;
		clone->Transform.Height = this->Transform.Height;
		for (int i = 0; i < _animations.Size(); i++)
		{
			clone->_animations.Add(_animations.ItemAt(i)->Clone(&clone->Transform));
		}

		return clone;
	};

	Animation* AddAnimation(std::string id, bool isRepeating, int frameCount)
	{
		Animation* animation = new Animation(id, isRepeating, frameCount, &Transform);
		_animations.Add(animation);
		return animation;
	}

	void Free()
	{
		for (int i = _animations.Size() - 1; i >= 0; i--)
		{
			Animation* item = _animations.ItemAt(i);
			_animations.RemoveAt(i);
			item->Free();
		}
	};

	std::string Id()
	{
		return _id;
	};

	FleeTransform Transform;
private:
	std::string _id;
	Animation * _activeAnimation;
	FleeList<Animation*> _animations;
};


class AnimationManager
{
public:
	static void Initialize();
	static AnimationSet*  GetAnimationsOf(std::string id);

private:
	AnimationManager();
	~AnimationManager();

	void Free();

	AnimationSet*  GetAnimationsSet(std::string id);

	bool Read();

	FleeList<AnimationSet> _templates;
	static AnimationManager* _current;
};

#endif
