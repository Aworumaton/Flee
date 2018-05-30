#ifndef AnimationManager_H
#define AnimationManager_H
#include "FleeRenderer.h"
#include "FleeList.h"


class Animation //coupled with animation 
{
public:
	struct KeyFrane
	{
		KeyFrane* NextFrame;

		SpriteData TextureData;
		int Duration;
	};

	Animation(std::string id)
	{
		_id = id;
	};

	std::string Id()
	{
		return _id;
	};

private:

	std::string _id;
	KeyFrane* _rootFrame;
};

class AnimationSet
{
public:

	bool SetAnimation(std::string id)
	{
		for (int i = 0; i < _animations.Size(); i++)
		{
			if (_animations.ItemAt(i).Id() == id)
			{
				_activeAnimation = &_animations.ItemAt(i);
				return true;
			}
		}

		return false;
	};

	AnimationSet Clone()
	{
		AnimationSet clone;
		clone._activeAnimation = this->_activeAnimation;

		for (int i = 0; i < _animations.Size(); i++)
		{
			clone._animations.Add(_animations.ItemAt(i));
		}

		return clone;
	};

private:
	Animation * _activeAnimation;
	FleeList<Animation> _animations;
};


class AnimationManager
{
public:
private:
	FleeList<AnimationSet> _templates;


	bool Read()
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
			std::string string_id = "";
			while (file >> string_id)
			{
				Flee_Animated_Sprite target;
				target.string_id = string_id;
				if (file.eof())
				{
					printf("Unable to parse sprite sheet file!\n");
					success = false;
					break;
				}
				
				file >> target.animation_frame_count;
				if (file.eof())
				{
					printf("Unable to parse sprite sheet file!\n");
					success = false;
					break;
				}
		
				target.animation_targets = new Flee_Sprite*[target.animation_frame_count];
				for (int i = 0; i < target.animation_frame_count; i++)
				{
					std::string sprite_id;
					if (file.eof())
					{
						printf("Unable to parse sprite sheet file!\n");
						success = false;
						break;
					}
					file >> sprite_id;
		
					target.animation_targets[i] = Get_Flee_Sprite(sprite_id);
				}
		
				if (capacity == _animated_sprite_count)
				{
					capacity = (int)(capacity * 1.8f);
					Flee_Animated_Sprite* new_set = new Flee_Animated_Sprite[capacity];
					for (int i = 0; i < _animated_sprite_count; i++)
					{
						new_set[i] = _animations[i];
					}
				//	delete(_tile_clips);
					_animations = new_set;
				}
		
				_animations[_animated_sprite_count] = target;
				_animated_sprite_count++;
			}
		
			//Close the file
			file.close();
		}
		
		//If the map was loaded fine
		return success;

	};
};



#endif
