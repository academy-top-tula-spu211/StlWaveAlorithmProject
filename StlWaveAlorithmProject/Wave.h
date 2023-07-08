#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

template <class T>
using matrix = vector<vector<T>>;

enum class CellType
{
	Start,
	Wall	= -5,
	Finish	= -10,
	Space	= -1
};

struct Cell
{
	int row;
	int column;

	friend bool operator==(Cell c1, Cell c2);
};

const vector<Cell> Offset{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

class Wave
{
	string fileMap;
	matrix<int> map;
	Cell cellStart;
	Cell cellFinish;
	vector<Cell> fronts[2];
	vector<Cell> way;
public:
	Wave(string fileName = "") : fileMap{fileName} {}

	string& FileMap() { return fileMap; }

	void CreateMap();
	bool MoveWave();
	void CreateWay();

	void ShowMap();
};

