#include "AnimationManager.h"


void AnimationManager::Initialize()
{

	if (_current != nullptr)
	{
		_current->Free();
	}

	_current = new AnimationManager();
}


AnimationSet*  AnimationManager::GetAnimationsOf(std::string id)
{
	return _current->GetAnimationsSet(id);
}

AnimationManager::AnimationManager()
{
	Read();
}

AnimationManager::~AnimationManager()
{
	Free();
}

void AnimationManager::Free()
{
	for (int i = _templates.Size() - 1; i >= 0; i--)
	{
		AnimationSet item = _templates.ItemAt(i);
		_templates.RemoveAt(i);
		item.Free();
	}
}


AnimationSet* AnimationManager::GetAnimationsSet(std::string id)
{
	for (int i = 0; i < _templates.Size(); i++)
	{
		if (_templates.ItemAt(i).Id() == id)
		{
			return _templates.ItemAt(i).Clone();
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
			AnimationSet* targetSet = new AnimationSet(id, animationCount);

			for (int i = 0; i < animationCount; i++)
			{

				std::string aniamtionId = "";
				file >> aniamtionId;

				int frameCount;
				file >> frameCount;


				int isRepeating;
				file >> isRepeating;

				Animation* animation = targetSet->AddAnimation(aniamtionId, isRepeating == 1, frameCount);

				for (int j = 0; j < frameCount; j++)
				{
					std::string frameId = "";
					file >> frameId;

					int frameDuration;
					file >> frameDuration;

					animation->AddKeyFrame(frameId, frameDuration);
				}
			}

			_templates.Add(*targetSet);
		}

		//Close the file
		file.close();
	}
	return success;

}

AnimationManager* AnimationManager::_current;
