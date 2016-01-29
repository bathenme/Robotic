
#include "Map.h"
#include "lodepng.h"
#include "iostream"
#include "fstream"

using namespace lodepng;

Map::Map(float mapResolution, float maprobotSize, const char* filePath) : mapResolution(mapResolution), maprobotSize(maprobotSize)
{
	robotSizeInCells = maprobotSize / mapResolution;
	inflationRaduis = 0.3 * robotSizeInCells;
	cout << "inflation Radius" << inflationRaduis << endl;
	decode(image,mapWidth,mapHeight,filePath);
	cout << "Map size: " << mapWidth<< ", " << mapHeight << endl;


}

void Map::loadMapFromFile()
{


	loadMap();
}

void Map::converImageToGrid()
{
	cout << "temp" << endl;
	map.resize(mapHeight);
	for (unsigned int i = 0; i<mapHeight; i++)
	{
		map[i].resize(mapWidth);
	}
}

void Map::loadMap()
{
	converImageToGrid();


	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			/*cout << "this is i: "<< i<< "and this is j: " << j << endl;*/
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}
	inflateObstacles();
	
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::inflateObstacles()
{
	
	inflatbleMap.resize(mapHeight);
	for (unsigned int i = 0; i<mapHeight; i++)
	{
		inflatbleMap[i].resize(mapWidth);
	}


	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			if (map[i][j])
			{

				for (unsigned a = (i - inflationRaduis); a < (i + inflationRaduis); a++)
				{
					for (unsigned b = (j - inflationRaduis); b < (j + inflationRaduis); b++)
					{
						if ((a >= 0 && a < mapHeight) && (b >= 0 && b < mapWidth))
						{
							inflatbleMap[a][b] = true;
						}
						
					}
				}
			}

		}
	}
	//printMap(inflatbleMap);
	pirntInfatablMapIntoPng();
	
}

void Map::printMap(vector<vector<bool> > map) const
{	
	ofstream myRoboticLab;
	myRoboticLab.open("myRoboticLab.txt");
	//cout << mapHeight << endl;
	//cout << mapWidth << endl;
	
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int k = 0; k < mapWidth; k++)
		{
			if (map[i][k])
			{
				myRoboticLab << "*";
			}
			else
			{
				myRoboticLab << " ";
			}
		}
		myRoboticLab << endl;
	}
	myRoboticLab.close();
}

bool Map::isTrueInflateableMap(int i, int j, int sizeToMerge)
{
	int startHeight = i*sizeToMerge;
	int startWidth = j*sizeToMerge;
	//cout << "i:" << i << " " << "j:" << j << endl;
	for (unsigned int a = startHeight; a < (startHeight + sizeToMerge); a++)
	{
		for (unsigned int b = startWidth; b < (startWidth + sizeToMerge); b++)
		{
			if (inflatbleMap[a][b] == true)
				return true;
		}
	}
	return false;
}
void Map::buildGrid(int sizeToMerge, Grid& mapToResize)
{	
	cout << mapHeight / sizeToMerge << " " << mapWidth / sizeToMerge << endl;
	mapToResize.resize(mapHeight / sizeToMerge);
	for (unsigned int i = 0; i < (mapHeight / sizeToMerge); i++)
	{
		mapToResize[i].resize(mapWidth / sizeToMerge);
	}

	for (unsigned int i = 0; i < (mapHeight / sizeToMerge); i++)
	{
		for (unsigned int j = 0; j < (mapWidth / sizeToMerge); j++)
		{
			if (isTrueInflateableMap(i, j, sizeToMerge))
			{
				mapToResize[i][j] = true;
			}
			else
				mapToResize[i][j] = false;

		}

	}
}

void Map::printGrid(const Grid grid, int mapheight, int mapwidth, const char* filePath) const
{
	ofstream myRoboticLab;
	myRoboticLab.open(filePath);
	//cout << mapHeight << endl;
	//cout << mapWidth << endl;

	for (unsigned int i = 0; i < mapheight; i++)
	{
		for (unsigned int k = 0; k < mapwidth; k++)
		{
			if (grid[i][k])
			{
				myRoboticLab << "*";
			}
			else
			{
				myRoboticLab << " ";
			}
		}
		myRoboticLab << endl;
	}
	myRoboticLab.close();
}

void Map::pirntInfatablMapIntoPng(){

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int k = 0; k < mapWidth; k++)
		{
			if (inflatbleMap[i][k])
			{
				int c = (i * mapWidth + k) * 4;
				image[c] = 0;
				image[c + 1] = 0;
				image[c + 2] = 0;

			}

		}
	}

	encode("inflatableRoboticLab.png", image, mapWidth, mapHeight);
}

Grid& Map::GetFineGrid()
{
	return fineGrid;
}

Grid& Map::GetCoarseGrid()
{
	return coarseGrid;
}

int Map::getRobotSizeInCells()
{
	return robotSizeInCells;
}

int Map::getMapHeight()
{
	return mapHeight;
}
int Map::getMapWidth()
{
	return mapWidth;
}


vector<unsigned char> Map::getImageVector()
{
	return image;
}
Grid& Map::getInflatableGrid(){
	return inflatbleMap;
}
Map::~Map() {
	// TODO Auto-generated destructor stub
}

