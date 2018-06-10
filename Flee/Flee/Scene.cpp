#include "Scene.h"
bool Scene::Read()
{
	//Success flag
	bool loaded = true;

	//Open the map
	std::ifstream map("Resources/level_0.txt");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		loaded = false;
	}
	else
	{
		//Determines what kind of tile will be made
		int columnSize = -1;
		int rowSize = -1;

		map >> columnSize;
		map >> rowSize;

		_levelWidth = columnSize * Tile::TILE_WIDTH;
		_levelHeight = rowSize * Tile::TILE_HEIGHT;

		_mapLayout = FleeList<Tile*>(columnSize*rowSize);
		for (int rowIndex = 0; rowIndex < rowSize; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < columnSize; columnIndex++)
			{
				int tileType;
				map >> tileType;


				Tile* tile = new Tile(tileType, columnIndex, rowIndex);
				_mapLayout.Add(tile);
			}
		}

		for (int rowIndex = 0; rowIndex < rowSize; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < columnSize; columnIndex++)
			{
				Tile* targetTile = _mapLayout.ItemAt(rowIndex  * columnSize + columnIndex);

				Tile* topTile = nullptr;
				Tile* bottomTile = nullptr;
				Tile* leftTile = nullptr;
				Tile* rightTile = nullptr;

				if (rowIndex > 0)
				{
					topTile = _mapLayout.ItemAt((rowIndex-1)  * columnSize + columnIndex);
				}
				if (rowIndex+1 < rowSize)
				{
					bottomTile = _mapLayout.ItemAt((rowIndex + 1)  * columnSize + columnIndex);
				}

				if (columnIndex > 0)
				{
					leftTile = _mapLayout.ItemAt(rowIndex * columnSize + columnIndex - 1);
				}
				if (columnIndex+1 < columnSize)
				{
					rightTile = _mapLayout.ItemAt(rowIndex * columnSize + columnIndex + 1);
				}
							
				targetTile->InitializeWith(topTile, bottomTile, leftTile, rightTile);
			}
		}
		//Close the file
		map.close();
	}



	//Open the map
	std::ifstream file("Resources/level_0_objects.txt");

	//If the map couldn't be loaded
	if (!file.is_open())
	{
		printf("Unable to load map objects file!\n");
		loaded = false;
	}
	else
	{
		std::string id = "";
		while (file >> id )
		{
			int x;
			int y;
			int variation;

			file >> variation;
			file >> x;
			file >> y;

			InteractiveGameObject* gameObject = nullptr;

			if (id == "Door")
			{
				gameObject = new Door(variation);
			}
			else if (id == "HidingPlace")
			{
				gameObject = new HidingPlace(variation);
			}

			//If the map couldn't be loaded
			if (gameObject == nullptr)
			{
				printf("Unable to load instantiate object!\n");
				loaded = false;
				break;
			}

			gameObject->Transform->X = x;
			gameObject->Transform->Y = y;
			_objects.Add(gameObject);
		}

		//Close the file
		file.close();
	}


	//If the map was loaded fine
	return loaded;
}

int Scene::GetLevelWidth()
{
	return _levelWidth;
}
int Scene::GetLevelHeight()
{
	return _levelHeight;
}

GameObject* Scene::GetFirstObjetUnder(SDL_Point point)
{
	for (int i = 0; i < _objects.Size(); i++)
	{
		GameObject* target = _objects.ItemAt(i);
		if (Constants::checkCollision(*target->Transform, point))
		{
			return target;
		}
	}

	return nullptr;
}

bool Scene::IsBlocked(FleeTransform* sourceTransform)
{
	//Go through the tiles
	for (int i = 0; i < _mapLayout.Size(); ++i)
	{
		Tile* sData = _mapLayout.ItemAt(i);
		//If the tile is a wall type tile
		if (sData->IsWall())
		{
			//If the collision box touches the wall tile
			if (Constants::CheckCollision(sourceTransform, sData->Transform()))
			{
				return true;
			}
		}
	}
	for (int i = 0; i < _objects.Size(); ++i)
	{
		GameObject* sData = _objects.ItemAt(i);
		//If the tile is a wall type tile
		if (sData->HasFlag(GameEntityFlags::Obstruction))
		{
			//If the collision box touches the wall tile
			if (Constants::CheckCollision(sourceTransform, sData->Transform))
			{
				return true;
			}
		}
	}
	
	//If no wall tiles were touched
	return false;
}

void Scene::Tick(int dt)
{
	for (int i = 0; i < _objects.Size(); ++i)
	{
		_objects.ItemAt(i)->Tick(dt);
	}
}

bool Scene::Initialize()
{
	if (!Read())
	{
		printf("Failed to load tile set!\n");
		return false;
	}
	return true;
}

Scene::~Scene()
{
}

Scene::Scene()
{	
}