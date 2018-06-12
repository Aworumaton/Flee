/*
*	Author: Omer Sari
*/
#ifndef InteractiveGameObject_H
#define InteractiveGameObject_H
#include "GameEntity.h"


class InteractiveGameObject : public GameObject
{
public:

	InteractiveGameObject(std::string visualId)
	{
		_visualData = AnimationManager::CreateAnimationsOf(visualId, Constants::VisualLayers::DynamicObjectsLayer);
		Transform = _visualData->Transform;
	};

	virtual ~InteractiveGameObject()
	{
		GameObject::~GameObject();
	};

	virtual void Tick(int dt) = 0;

protected:
	InteractiveGameObject() {};
	AnimationData * _visualData;
};















class Door : public InteractiveGameObject
{
public:
	Door(int variation)
	{
		_visualData = AnimationManager::CreateAnimationsOf("Door", Constants::VisualLayers::DynamicObjectsLayer);
		Transform = _visualData->Transform;
		Close();
	};

	virtual ~Door()
	{
		InteractiveGameObject::~InteractiveGameObject();
	};

	virtual void Tick(int dt)
	{

	};

	virtual bool HasFlag(GameEntityFlags::FlagTypes flag)
	{
		return (flag & GameEntityFlags::FlagTypes::Door) != 0 || (!_isOpened && ((flag & GameEntityFlags::FlagTypes::Obstruction) != 0));
	};

	void Toggle()
	{
		if (_isOpened)
		{
			Close();
		}
		else
		{
			Open();
		}
	};
private:
	bool _isOpened;

	void Close()
	{
		_isOpened = false;
		_visualData->SetAnimation("Closed");
	};

	void Open()
	{
		_isOpened = true;
		_visualData->SetAnimation("Opened");
	};
};









class HidingPlace : public InteractiveGameObject
{
public:
	HidingPlace(int variation)
	{
		_visualData = AnimationManager::CreateAnimationsOf("Closet", Constants::VisualLayers::DynamicObjectsLayer);
		Transform = _visualData->Transform;
	};

	virtual ~HidingPlace()
	{
		InteractiveGameObject::~InteractiveGameObject();
	};

	virtual void Tick(int dt)
	{

	};

	virtual bool HasFlag(GameEntityFlags::FlagTypes flag)
	{
		return (flag & (GameEntityFlags::FlagTypes::Hiding_Place | GameEntityFlags::FlagTypes::Obstruction)) != 0;
	};
};
#endif

