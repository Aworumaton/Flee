#include "Map_Creator.h"
void Map_Creator::close(Flee_Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < Constants::TOTAL_TILES; ++i)
	{
		if (tiles[i] == NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	//Free loaded images

	_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
}

bool Map_Creator::setTiles(Flee_Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("Resources/lazy.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < Constants::TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < Constants::TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Flee_Tile(x, y, tileType, _renderer, &gTileClips[tileType]);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += Constants::TILE_WIDTH;

			//If we've gone too far
			if (x >= Constants::LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += Constants::TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[Constants::Tile_Type::TILE_RED].x = 0;
			gTileClips[Constants::Tile_Type::TILE_RED].y = 0;
			gTileClips[Constants::Tile_Type::TILE_RED].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_RED].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_GREEN].x = 0;
			gTileClips[Constants::Tile_Type::TILE_GREEN].y = 80;
			gTileClips[Constants::Tile_Type::TILE_GREEN].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_GREEN].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_BLUE].x = 0;
			gTileClips[Constants::Tile_Type::TILE_BLUE].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BLUE].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_BLUE].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_LEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_LEFT].y = 80;
			gTileClips[Constants::Tile_Type::TILE_LEFT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_LEFT].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].h = Constants::TILE_HEIGHT;
					  
			gTileClips[Constants::Tile_Type::TILE_TOP].x = 160;
			gTileClips[Constants::Tile_Type::TILE_TOP].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOP].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_TOP].h = Constants::TILE_HEIGHT;
					  
			gTileClips[Constants::Tile_Type::TILE_CENTER].x = 160;
			gTileClips[Constants::Tile_Type::TILE_CENTER].y = 80;
			gTileClips[Constants::Tile_Type::TILE_CENTER].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_CENTER].h = Constants::TILE_HEIGHT;
				
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].x = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].h = Constants::TILE_HEIGHT;
					  
			gTileClips[Constants::Tile_Type::TILE_RIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].y = 80;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].h = Constants::TILE_HEIGHT;
					   
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].w = Constants::TILE_WIDTH;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].h = Constants::TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}


void Map_Creator::Tick(float dt)
{


	//Clear screen
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(_renderer);

	//Render level
	for (int i = 0; i < Constants::TOTAL_TILES; ++i)
	{
		_tileSet[i]->render(*_camera);
	}


	//Update screen
	SDL_RenderPresent(_renderer);
}

Map_Creator::~Map_Creator()
{
	close(_tileSet);
}

Map_Creator::Map_Creator(SDL_Renderer* renderer, SDL_Rect* camera)
{
	_renderer = renderer;
	//Level camera
	_camera = camera;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (_renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}
	
	//Load the level tiles
	_tileSet = new Flee_Tile*[Constants::TOTAL_TILES];
	if (!setTiles(_tileSet))
	{
		printf("Failed to load tile set!\n");
		return;
	}
}