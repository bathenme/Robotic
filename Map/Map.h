

#ifndef MAP_H_
#define MAP_H_

#include <vector>
using namespace std;

typedef vector<vector<bool> > Grid;

class Map {
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	vector<unsigned char> image;
	vector<vector<bool> > map;
	float mapResolution;
	float robotSize;
	int robotSizeInCells;
	int inflationRaduis;

	Grid fineGrid; //each cell in the size of the robot
	Grid coarseGrid; //each cell in the size 2x2of the fine grid cell
	Grid inflatbleMap; //inflate grid depends the robot radius
	void converImageToGrid();
	void loadMap();
	void pirntInfatablMapIntoPng();
	bool checkIfCellIsOccupied(int i, int j);
	bool isTrueInflateableMap(int i, int j, int sizeToMerge);
public:
	Map(float mapResolution, float robotSize, const char* filePath);
	void printMap(vector<vector<bool> > map) const;
	void printGrid(const Grid grid, int mapheight, int mapwidth, const char* filePath) const;
	void inflateObstacles();
	void buildGrid(int robotSizeInCells, Grid& mapToResize);
	Grid& GetFineGrid();
	Grid& GetCoarseGrid();
	Grid& getInflatableGrid();
	int getRobotSizeInCells();
	int getMapHeight();
	int getMapWidth();
	vector<unsigned char> getImageVector();

	virtual ~Map();
};


#endif /* MAP_H_ */
